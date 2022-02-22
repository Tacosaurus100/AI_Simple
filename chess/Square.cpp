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
   Connect(id, wxEVT_THREAD, (wxObjectEventFunction) &Square::onClick);
}

Square::Square(std::string position) {
   this->position = position;
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
   // std::cout << "square clicked\n";
   Board* board = (Board*) (GetParent());
   board->moveHelper(this->position);
}

void Square::clickNoGUI(wxWindow* board) {
   ((Board*) board)->moveHelper(this->position);
}

void Square::destroy() {
   std::cout << "is main destroy " << wxThread::IsMain () << '\n';
   if (wxThread::IsMain ()) {
      this->DestroyChildren();
   } else {
      wxThreadEvent evt( wxEVT_CHECKBOX, this->GetId());
      wxTheApp->QueueEvent (evt.Clone()); 
      std::this_thread::sleep_for (std::chrono::microseconds(250000)); 
      if (wxTheApp->HasPendingEvents()) { 
         wxTheApp->ProcessPendingEvents();
      }
      std::this_thread::sleep_for (std::chrono::microseconds(250000));
   }
}

#endif