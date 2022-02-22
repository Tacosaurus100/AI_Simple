#ifndef CHESS_SQUARE_HPP
#define CHESS_SQUARE_HPP

#include <string>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

using namespace std;

namespace chess {
   class Square : public wxPanel{
      public: 
         Square(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, std::string position);
         Square(std::string position);

         void onClick();
         void clickNoGUI(wxWindow* board);

         static int* parsePos (std::string pos,  bool promotional = false);

         static Square* getSquare (Square*** squares, std::string pos, bool promotional = false);

         void destroy();

         std::string position;
   };
}

#endif