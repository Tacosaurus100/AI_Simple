#ifndef CHESS_PROMOTION_MENU_CPP
#define CHESS_PROMOTION_MENU_CPP

#include <chess/PromotionMenu.hpp>
#include <chess/PromotionPiece.cpp>
#include <chess/Square.cpp>
#include <cmath>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
 
using namespace chess;

PromotionMenu::PromotionMenu(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame*)NULL, WINDOW_ID, title, pos, size)
{

}

PromotionMenu::PromotionMenu() {

}

void PromotionMenu::init(PromotionMenu* frame) {
   const int SQUARE_ID = 85;
   const int PIECE_ID = SQUARE_ID + 4;
   wxPoint* point = new wxPoint (-1, -1);
   wxSize* minSize = new wxSize (BORDER_WIDTH * 2 + BOX_WIDTH * 8, BORDER_WIDTH * 2 + BOX_WIDTH * 8);
   if (GUI) {
      frame->SetMinClientSize (*minSize);
      frame->SetMaxClientSize (*minSize);
   }
   
   wxPoint* boxPoint;
   wxSize* boxSize = new wxSize (BOX_WIDTH, BOX_WIDTH);
   frame->squares = new Square** [2];
   for (int i = 0; i < 2; i++) {
      frame->squares[i] = new Square* [2];
      for (int j = 0; j < 2; j++) {
         boxPoint = new wxPoint (BORDER_WIDTH + BOX_WIDTH * i + 4, BORDER_WIDTH + BOX_WIDTH * j);
         if (GUI) {
            frame->squares[i][j] = new Square(frame, SQUARE_ID + i * 2 + j, *boxPoint, *boxSize, std::string(1, (char) (i + 97)) + (char) (1 + 49 - j));
            frame->squares[i][j]->SetBackgroundColour((i + j) % 2 == 0 ? wxColour(* wxWHITE) : wxColour(* wxBLUE));
         } else {
            frame->squares[i][j] = new Square(std::string(1, (char) (i + 97)) + (char) (1 + 49 - j));
         }
      }
   }
   
   // initialize the pieces and their values
   frame->pieces = new PromotionPiece* [8];

   string* currentPath = new string (filesystem::current_path());

   if (GUI) {
      wxBitmap* newBitmap;
      wxImage* img;
      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Knight.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[0] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "a2", true), PIECE_ID + 0, false, "knight"); 

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Bishop.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[1] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "b2", true), PIECE_ID + 1, false, "bishop");

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Rook.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[2] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "a1", true), PIECE_ID + 2, false, "rook"); 

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Queen.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[3] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "b1", true), PIECE_ID + 3, false, "queen");

      img = new wxImage(*currentPath + "/Chess_Pieces/White_Knight.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[4] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "a2", true), PIECE_ID + 4, true, "knight"); 

      img = new wxImage(*currentPath + "/Chess_Pieces/White_Bishop.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[5] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "b2", true), PIECE_ID + 5, true, "bishop");

      img = new wxImage(*currentPath + "/Chess_Pieces/White_Rook.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[6] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "a1", true), PIECE_ID + 6, true, "rook"); 

      img = new wxImage(*currentPath + "/Chess_Pieces/White_Queen.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      frame->pieces[7] = new PromotionPiece (newBitmap, Square::getSquare(frame->squares, "b1", true), PIECE_ID + 7, true, "queen");
   } else {
      frame->pieces[0] = new PromotionPiece (false, "knight"); 
      frame->pieces[1] = new PromotionPiece (false, "bishop");
      frame->pieces[2] = new PromotionPiece (false, "rook");
      frame->pieces[3] = new PromotionPiece (false, "queen");
      frame->pieces[4] = new PromotionPiece (true, "knight"); 
      frame->pieces[5] = new PromotionPiece (true, "bishop");
      frame->pieces[6] = new PromotionPiece (true, "rook"); 
      frame->pieces[7] = new PromotionPiece (true, "queen");
   }
}

void PromotionMenu::promote (PromotionPiece* piece) {
   Board* board = (Board*) this->board; 
   Square* square = (Square*) board->getSquare(std::string(1, board->prevMove[board->prevMove.length() - 2]) + board->prevMove[board->prevMove.length() - 1]);
   int* parsed = Square::parsePos(square->position);
   Piece* promote = board->getPieceAt(parsed[0], parsed[1]);
   
   delete parsed;
   
   if (GUI) {
      promote->SetBitmap (piece->GetBitmap());
   }
   promote->name = piece->name;
   
   if (GUI) {
      this->Show(false);
   }
   board->promotionMenuIsActive = false;
   board->isWhitesTurn = false;
}

void PromotionMenu::show (bool isWhite) {
   int index = 4;
   if (!isWhite) {
      index = 0;
   }
   for (int i = 0; i < 4; i++) {
      this->pieces[i + index]->Show(true);
   }
   for (int i = 4; i < 8; i++) {
      this->pieces[i - index]->Show(false);
   }
   if (GUI) {
      this->Show(true);
   }
   ((Board*) this->board)->isWhitesTurn = !((Board*) this->board)->isWhitesTurn;
}

#endif