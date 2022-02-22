#ifndef CHESS_PIECE_CPP
#define CHESS_PIECE_CPP

#include <chess/Piece.hpp>
#include <chess/Board.hpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
#include <wx/colour.h>
 
using namespace chess;

Piece::Piece(wxBitmap* bitmap, wxWindow* parent, int id, const std::string position, const bool isWhite, const std::string name)
	: wxStaticBitmap(parent, id, *bitmap, *(new wxPoint (-2, 0)), *(new wxSize (82, 80)))
{
   this->position = position;
   this->isWhite = isWhite;
   this->name = name;
   this->moved = false;

   Bind(wxEVT_LEFT_DOWN, (wxObjectEventFunction) &Piece::onClick, this, id);
   Bind(wxEVT_THREAD, (wxObjectEventFunction) &Piece::onClick, this, id);
}

Piece::Piece(const std::string position, const bool isWhite, const std::string name) {
   this->position = position;
   this->isWhite = isWhite;
   this->name = name;
   this->moved = false;
}

void Piece::onClick() {
   // std::cout << "piece clicked\n";
   Board* board = (Board*) (GetParent()->GetParent());
   board->unhighlight();
   if (board->activePiece != nullptr) {
      board->activePiece->unhighlight();
   }
   if (board->isWhitesTurn == this->isWhite) {
      this->highlight();
   }
   
   board->moveHelper(this->position, this);
}

void Piece::clickNoGUI(wxWindow* board) {
   if (((Board*) board)->activePiece != nullptr) {
      ((Board*) board)->activePiece->unhighlight();
   }
   
   ((Board*) board)->moveHelper(this->position, this);
}

void Piece::highlight() { 
   if (GUI) {
      this->SetOwnBackgroundColour (*color);
      this->Refresh();
   }
}

void Piece::unhighlight() { 
   if (GUI) {
      if (this->GetParent() != nullptr) {
         this->SetOwnBackgroundColour (this->GetParent()->GetBackgroundColour());
         this->Refresh();
      }
   }
}

void Piece::reparent (wxThreadEvent& event) {
   Board* board = (Board*) (GetParent()->GetParent());

   std::cout << "space to reparent" << ((Square*) board->getSquare(event.GetString().ToStdString()))->position << '\n';
   // exit (0);
   if (GUI) {
      this->Reparent(((Square*)board->getSquare(event.GetString().ToStdString())));
   }
   std::cout << "after reparent\n";
   // exit (0);
}

std::string Piece::move(std::string position, bool isCapture) {
   std::string move = "";
   if (this->name == "knight") {
      move += "N";
   } else if (this->name == "pawn") {
      if (isCapture) {
         move += this->position[0];
      }
   } else {
      move += (char) ((int) this->name[0] - 32);
   }
   if (isCapture) {  
      move += "x";
   }
   move += position;

   this->moved = true;
   this->position = position;
   return move;
}

Piece::~Piece() {
   delete color;
}

#endif