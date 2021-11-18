#ifndef CHESS_PROMOTION_PIECE_CPP
#define CHESS_PROMOTION_PIECE_CPP

#include <chess/PromotionPiece.hpp>
#include <chess/PromotionMenu.cpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
 
using namespace chess;

PromotionPiece::PromotionPiece(wxBitmap* bitmap, wxWindow* parent, int id, const std::string position, const bool isWhite, const std::string name)
	: wxStaticBitmap(parent, id, *bitmap, *(new wxPoint (-2, 0)))
{
   this->isWhite = isWhite;
   this->name = name;
   Connect(id, wxEVT_LEFT_DOWN, (wxObjectEventFunction) &PromotionPiece::onClick);
}

void PromotionPiece::onClick() {
   PromotionMenu* pm = (PromotionMenu*) (GetParent()->GetParent());
   pm->promote(this);
}

#endif