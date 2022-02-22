#ifndef CHESS_AI_CPP
#define CHESS_AI_CPP

#include <unistd.h>
#include <thread>
#include <chrono>

#include <chess/artificialIntelligence/ChessAI.hpp>
#include <chess/Piece.hpp>
#include <chess/Player.hpp>
#include <chess/Square.hpp>

#include <wx/event.h>

#include <artificialIntelligence/classes/BasicLayerList.cpp>

ChessAI::ChessAI (bool isWhite, BasicLayerList<float>* model){
   this->isWhite = isWhite;
   std::cout << (this->isWhite ? "White" : "Black") << " AI\n";
   this->counter = 0;
   this->inputStates = new Matrix3D<float>* [MAX_MOVES];
   this->outputMoves = new std::string [MAX_MOVES];
   this->pieceMoved = new int [MAX_MOVES];
   this->model = model;
}

Matrix3D<float>* ChessAI::generateInput (Board* board, int isWhite) {
   Matrix3D<float>* matrixBoard = new Matrix3D<float>(1, 8, 8);
   Player* player = isWhite ? (Player*) board->pw : (Player*) board->pb;
   Player* player2 = isWhite ? (Player*) board->pb : (Player*) board->pw;

   for (int i = 0; i < 16; i++) {
      if (player->pieces[i] != nullptr) {
         int* parsed = Square::parsePos(player->pieces[i]->position);
         if (player->pieces[i]->name == "pawn") {
            matrixBoard->insert(1, 0, parsed[1], parsed[0]);
         } else if (player->pieces[i]->name == "knight") {
            matrixBoard->insert(3, 0, parsed[1], parsed[0]);
         } else if (player->pieces[i]->name == "bishop") {
            matrixBoard->insert(3, 0, parsed[1], parsed[0]);
         } else if (player->pieces[i]->name == "rook") {
            matrixBoard->insert(5, 0, parsed[1], parsed[0]);
         } else if (player->pieces[i]->name == "queen") {
            matrixBoard->insert(9, 0, parsed[1], parsed[0]);
         } else if (player->pieces[i]->name == "king") {
            matrixBoard->insert(20, 0, parsed[1], parsed[0]);
         } else {
            matrixBoard->insert(0, 0, parsed[1], parsed[0]);
         } 
      }

      if (player2->pieces[i] != nullptr && (player->pieces[i] != nullptr && player->pieces[i]->position != player2->pieces[i]->position && !board->isWhitesTurn)) {
         int* parsed = Square::parsePos(player2->pieces[i]->position);
         if (player2->pieces[i]->name == "pawn") {
            matrixBoard->insert(-1, 0, parsed[1], parsed[0]);
         } else if (player2->pieces[i]->name == "knight") {
            matrixBoard->insert(-3, 0, parsed[1], parsed[0]);
         } else if (player2->pieces[i]->name == "bishop") {
            matrixBoard->insert(-3, 0, parsed[1], parsed[0]);
         } else if (player2->pieces[i]->name == "rook") {
            matrixBoard->insert(-5, 0, parsed[1], parsed[0]);
         } else if (player2->pieces[i]->name == "queen") {
            matrixBoard->insert(-9, 0, parsed[1], parsed[0]);
         } else if (player2->pieces[i]->name == "king") {
            matrixBoard->insert(-20, 0, parsed[1], parsed[0]);
         } else {
            matrixBoard->insert(0, 0, parsed[1], parsed[0]);
         } 
      }
   }

   return matrixBoard;
}

void ChessAI::makeRandomMove (Board* board) {

   Player* player = this->isWhite ? (Player*) board->pw : (Player*) board->pb;
   
   std::string finalPos;
   int pieceIndex = -1;
   inputStates[counter] = ChessAI::generateInput (board, this->isWhite);

   while (this->isWhite == board->isWhitesTurn && !board->promotionMenuIsActive && board->gameOver == 0) {
      if (board->checkmate()) {
         board->gameOver = -1;
      }
      if (board->stalemate()) {
         board->gameOver = -0.1;
      }

      // std::cout << "random try\n";
      board->activePiece = nullptr;
      Piece* piece = nullptr;
      while (piece == nullptr) {
         pieceIndex = (int) math::rand(0, 16);
         piece = player->pieces[pieceIndex];
      }

      std::string* validMoves = board->getValidMoves(piece);
      if (piece->validMoveCount != 0) {
         finalPos = validMoves[(int) math::rand(0, piece->validMoveCount)];

         Square* square = Square::getSquare (board->squares, finalPos);
         makeMove (board, square, piece);
      }
   }
   if (GUI) {
      std::this_thread::sleep_for (std::chrono::microseconds(1500000));
   }
   
   if (pieceIndex != -1) {
      pieceMoved[counter] = pieceIndex;
      outputMoves[counter++] = finalPos;
   }

   if (counter == MAX_MOVES) {
      std::cout << "counter overload";
      board->gameOver = 0.01;
   }
}

void ChessAI::makeDeterminedMove (Board* board) {
   if (this->isWhite != board->isWhitesTurn || board->promotionMenuIsActive) {
      return;
   }
   // std::cout << " " << this->isWhite << " " << board->promotionMenuIsActive;
   Player* player = this->isWhite ? (Player*) board->pw : (Player*) board->pb;
   std::string finalPos = "";

   // std::cout << "making new determined move\n";

   // get values from output layer
   Matrix3D<float>* output = model->getLast ()->getLayerMatrix();
   float v = -10000;
   int pieceIndex = -1;
   std::string decisionPos = "";

   for (int i = 0; i < 16; i++) {
      Piece* piece = player->pieces[i];
      if (piece != nullptr) {

         // test all of the moves and select the best one
         std::string* validMoves = board->getValidMoves(piece);
         std::string currentPos = piece->position;
         if (piece->validMoveCount != 0) {
            for (int j = 0; j < piece->validMoveCount; j++) {
               finalPos = validMoves[j];


               // move the piece without actually moving the piece
               board->confirmMove(piece, finalPos, false);
               model->editRootMatrix (ChessAI::generateInput (board, this->isWhite));
               model->calculateAndUpdateAll ();
               // model->getRoot()->getLayerMatrix()->printMatrix();
               // model->getLast()->getLayerMatrix()->printMatrix();
               // std::cout << *model->getLast()->getLayerMatrix()->getData(0, 0, 0) << '\n';
               if (v < *model->getLast()->getLayerMatrix()->getData(0, 0, 0)) {
                  v = *model->getLast()->getLayerMatrix()->getData(0, 0, 0);
                  pieceIndex = i;
                  decisionPos = finalPos;
               }
            }
            board->confirmMove(piece, currentPos, false);
         }
      }
   }
   

   // for (int i = 0; i < )
   // for (int i = 0; i < 64; i++) {
   //    if (v < *output->getData(0, 0, i)) {
   //       pos = i;
   //       v = *output->getData(0, 0, i);
   //    }
   // }
   // v = 0;
   // for (int i = 64; i < 80; i++) {
   //    if (v < *output->getData(0, 0, i)) {
   //       pieceIndex = i - 64;
   //       v = *output->getData(0, 0, i);
   //    }
   // }

   // enact move
   if (pieceIndex != -1) {
      inputStates[counter] = ChessAI::generateInput (board, this->isWhite);
      int* parsed = Square::parsePos(decisionPos);
      Square* square = board->squares[parsed[0]][parsed[1]];
      if (square != nullptr && player->pieces[pieceIndex] != nullptr) {
         makeMove(board, square, player->pieces[pieceIndex]);
      }

      if (this->isWhite != board->isWhitesTurn || board->promotionMenuIsActive) {
         pieceMoved[counter] = pieceIndex;
         outputMoves[counter++] = finalPos;  
      }
   } 
   if (this->isWhite == board->isWhitesTurn && !board->promotionMenuIsActive) {
      if (player->pieces[pieceIndex] == nullptr) {
         std::cout << "determined move failed due to piece being nullptr \n";
      } else {
         std::cout << "determined move failed due to invalid move of " << player->pieces[pieceIndex]->name << " at " << player->pieces[pieceIndex]->position << '\n';
      }
      makeRandomMove (board);
   }

   if (counter == MAX_MOVES) {
      std::cout << "counter overload";
      board->gameOver = 0.01;
   }
}

void ChessAI::makeMove (Board* board, Square* square, Piece* piece) {
   int* parsed = Square::parsePos(square->position);
   // generateInput(board, piece->isWhite)->printMatrix();
   if (!board->pieceAtPositionEither(parsed[0], parsed[1])) {
      if (GUI) {
         wxThreadEvent evt( wxEVT_THREAD, piece->GetId());
         wxTheApp->QueueEvent(evt.Clone());

         std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));

         wxThreadEvent evt2( wxEVT_THREAD, square->GetId());
         wxTheApp->QueueEvent(evt2.Clone());

         std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));

         if (wxTheApp->HasPendingEvents()) {
            wxTheApp->ProcessPendingEvents ();
         }
      } else {
         piece->clickNoGUI(board);
         square->clickNoGUI(board);
      }

   } else if (board->pieceAtPosition(square->position, !piece->isWhite)){
      
      if (GUI) {
         wxThreadEvent evt( wxEVT_THREAD, piece->GetId());
         wxTheApp->QueueEvent(evt.Clone());

         if (wxTheApp->HasPendingEvents()) {
            wxTheApp->ProcessPendingEvents ();
         }

         std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));

         wxThreadEvent evt2( wxEVT_THREAD, board->getPieceAt(parsed[0], parsed[1])->GetId());
         wxTheApp->QueueEvent(evt2.Clone());

         std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));

         if (wxTheApp->HasPendingEvents()) {
            wxTheApp->ProcessPendingEvents ();
         }
      } else {
         piece->clickNoGUI(board);
         board->getPieceAt(parsed[0], parsed[1])->clickNoGUI(board);
      }
   }
   delete parsed;
}



#endif 