#ifndef CHESS_SQUARE_CPP
#define CHESS_SQUARE_CPP

#include <chess/Square.hpp>
#include <chess/Board.hpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
 
using namespace chess;

Square::Square(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, std::string position)
	: wxPanel(parent, id, pos, size)
{
   this->position = position;
   Connect(id, wxEVT_LEFT_DOWN, (wxObjectEventFunction) &Square::onClick);
}

int* Square::parsePos (std::string pos, bool promotional) {
   int* arr = new int [2];
   if (promotional) {
      arr[0] = (int) pos[0] - 97;
      arr[1] = 1 - ((int) pos[1] - 49);
      return arr;
   }
   arr[0] = (int) pos[0] - 97;
   arr[1] = 7 - ((int) pos[1] - 49);
   return arr;
}

Square* Square::getSquare (Square*** squares, std::string pos, bool promotional) {
   int* arr = Square::parsePos (pos, promotional);
   Square* panel = squares[arr[0]][arr[1]];
   delete[] arr;
   return panel;
}

void Square::onClick() {
   Board* board = (Board*) (GetParent());
   board->moveHelper(this->position);
}

#endif