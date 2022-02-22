#ifndef PLAYCHESS_CPP
#define PLAYCHESS_CPP


#define GAME_TYPE 3
#define GUI 1
// #define GUI GAME_TYPE != 3
#define SMART_WHITE 1
#define SMART_BLACK 1
#define ITERATION "1"
#define TEST_AI 1
#define SLEEP_TIME 100000

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>

#include <sys/time.h>
#include <sys/resource.h>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
#include <wx/evtloop.h>

#include "playChess.hpp"

#include <chess/Board.cpp>
#include <chess/PromotionMenu.cpp>
#include <chess/Piece.cpp>
#include <chess/PlayerWhite.cpp>
#include <chess/PlayerBlack.cpp>
#include <chess/artificialIntelligence/ChessAI.cpp>
#include <chess/artificialIntelligence/trainChessAI.cpp>

#include <artificialIntelligence/classes/BasicLayerList.cpp>


using namespace chess;
using namespace std;

IMPLEMENT_APP_NO_MAIN(PlayChess)

void runAI (ChessAI* white, ChessAI* black, Board* board, wxApp* app) {
   std::thread currentAIThread;

   while (board->gameOver == 0) {
      // try to make a move every 0.5 seconds
      if (white != nullptr) {
         if (SMART_WHITE) {
            currentAIThread = std::thread(&ChessAI::makeDeterminedMove, white, board);
         } else {
            currentAIThread = std::thread(&ChessAI::makeRandomMove, white, board);
         }
         currentAIThread.join();
         if (board->promotionMenuIsActive && board->isWhitesTurn) {
            std::cout << board->pw->piecesThatExist();
            std::cout << "promoting\n";
            PromotionPiece* piece = ((PromotionMenu*)board->promotionMenu)->pieces[7];

            ((PromotionMenu*) board->promotionMenu)->promote(piece);
            std::cout << board->pw->piecesThatExist();
            std::cout << "promote complete\n";
         }
      }

      if (board->gameOver == 0 && black != nullptr) {
         if (SMART_BLACK) {
            currentAIThread = std::thread(&ChessAI::makeDeterminedMove, black, board);
         } else {
            currentAIThread = std::thread(&ChessAI::makeRandomMove, black, board);
         }
         currentAIThread.join();

         if (board->promotionMenuIsActive && !board->isWhitesTurn) {
            PromotionPiece* piece = ((PromotionMenu*)board->promotionMenu)->pieces[3];

            ((PromotionMenu*) board->promotionMenu)->promote(piece);
         }
      }

   }
   
   if (white != nullptr) {
      BasicLayerList<float>* modelWhite = chess::artificialIntelligence::train::trainNetwork (white, board->gameOver);
      std::string csvPath = ((std::string) filesystem::current_path()) + "/Model_Outputs/whiteAIModel" + ITERATION + ".csv";
      white->model->toFile (csvPath);
   }
   if (black != nullptr) {
      BasicLayerList<float>* modelBlack = chess::artificialIntelligence::train::trainNetwork (black, -board->gameOver);
      std::string csvPath = ((std::string) filesystem::current_path()) + "/Model_Outputs/blackAIModel" + ITERATION + ".csv";
      black->model->toFile (csvPath);
   }

   if (TEST_AI) {
      std::cout << board->gameOver << '\n';
      std::this_thread::sleep_for (std::chrono::microseconds(1000000));
   }

   exit(0);
}

int main(int argc, char *argv[])
{
   if (GUI) {
      wxEntryStart( argc, argv );
      wxTheApp->CallOnInit();

      wxInitAllImageHandlers();
   }
   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../../chess";
   filesystem::current_path(filesystem::path(*currentPath));
   
   Board* board = new Board(wxT("Chess"), wxPoint(-1,-1), wxSize(670,698));
   Board::init (board);
   
   PromotionMenu* promotionMenu;
   if (GUI) {
      promotionMenu = new PromotionMenu(wxT("Promotion"), wxPoint(-1,-1), wxSize(190,218));
   } else {
      promotionMenu = new PromotionMenu();
   }
   PromotionMenu::init (promotionMenu);
   board->pb = new PlayerBlack (board->squares);
   board->pw = new PlayerWhite (board->squares);

   board->promotionMenu = promotionMenu;
   promotionMenu->board = board;

   for (int i = 0; i < 16; i++) {
      board->getValidMoves(board->pw->pieces[i]);
      board->getValidMoves(board->pb->pieces[i]);
   }
   
   if (GUI) {
      wxTheApp->Bind(wxEVT_COMBOBOX, (wxObjectEventFunction) &Board::reparent, board, board->GetId());

      for (int i = 0; i < 16; i++) {

         wxTheApp->Bind(wxEVT_THREAD, (wxObjectEventFunction) &Piece::onClick, board->pb->pieces[i], (100 + i));
         wxTheApp->Bind(wxEVT_THREAD, (wxObjectEventFunction) &Piece::onClick, board->pw->pieces[i], (200 + i));
         // wxTheApp->Bind(wxEVT_CHECKLISTBOX, (wxObjectEventFunction) &wxWindow::Reparent, board->pw->pieces[i], (100 + i));
         // wxTheApp->Bind(wxEVT_CHECKLISTBOX, (wxObjectEventFunction) &wxWindow::Reparent, board->pw->pieces[i], (200 + i));
         board->pb->pieces[i]->SetCanFocus (true);
         board->pw->pieces[i]->SetCanFocus (true);
         // wxTheApp->Bind(wxEVT_COMBOBOX, (wxObjectEventFunction) &Piece::reparent, board->pw->pieces[i], (100 + i));
         // wxTheApp->Bind(wxEVT_COMBOBOX, (wxObjectEventFunction) &Piece::reparent, board->pw->pieces[i], (200 + i));
      }

      for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
            wxTheApp->Bind(wxEVT_THREAD, (wxObjectEventFunction) &Square::onClick, board->squares[i][j], (20 + i * 8 + j));
            wxTheApp->Bind(wxEVT_CHECKBOX, (wxObjectEventFunction) &Square::destroy, board->squares[i][j], (20 + i * 8 + j));
            board->squares[i][j]->SetCanFocus (true);
         }
      }

      wxTheApp->Bind(wxEVT_COMBOBOX_CLOSEUP, (wxObjectEventFunction) &PlayChess::onClick, wxTheApp, wxID_ANY);
   }

   std::thread AIThread;
   ChessAI* whiteAI = nullptr;
   ChessAI* blackAI = nullptr;

   // white ai
   if (GAME_TYPE == 1 || GAME_TYPE == 3) {
      std::string csvPath = ((std::string) filesystem::current_path()) + "/Model_Outputs/blackAIModel" + ITERATION + ".csv";
      BasicLayerList<float>* model = BasicLayerList<float>::loadFromFile(csvPath);
      if (model == nullptr) {
         //make one
         model = chess::artificialIntelligence::train::generateModel();
      }
      whiteAI = new ChessAI(true, model);
   } 

   // black ai
   if (GAME_TYPE == 2 || GAME_TYPE == 3){
      std::string csvPath = ((std::string) filesystem::current_path()) + "/Model_Outputs/blackAIModel" + ITERATION + ".csv";
      BasicLayerList<float>* model = BasicLayerList<float>::loadFromFile(csvPath);
      if (model == nullptr) { 
         model = chess::artificialIntelligence::train::generateModel();
      }
      blackAI = new ChessAI(false, model);
   }

   // run it
   if (whiteAI != nullptr || blackAI != nullptr) {
      AIThread = std::thread(runAI, whiteAI, blackAI, board, wxTheApp);
   }

   if (GUI) {
      board->Show(true);

      wxTheApp->OnRun();
   }
   else {
      // just timeout after 100 seconds
      for (int i = 0; i < 100; i++) {
         std::this_thread::sleep_for (std::chrono::microseconds(1000000));
      }
   }
   
   return 0;
}

void PlayChess::onClick () {
   // std::cout << "finally is main " << wxThread::IsMain () << '\n';
   // std::cout << "finally\n";
}

#endif