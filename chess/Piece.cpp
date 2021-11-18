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

   Connect(id, wxEVT_LEFT_DOWN, (wxObjectEventFunction) &Piece::onClick);
}

void Piece::onClick() {
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

void Piece::highlight() { 
   this->SetOwnBackgroundColour (*color);
   this->Refresh();
}

void Piece::unhighlight() { 
   this->SetOwnBackgroundColour (this->GetParent()->GetBackgroundColour());
   this->Refresh();
}

std::string Piece::move(std::string position) {
   this->moved = true;
   this->position = position;
   if (this->name == "knight") {
      return "N" + position;
   } else if (this->name == "pawn") {
      return position;
   } else {
      return (char) ((int) this->name[0] - 32) + position;
   }
}

#endif