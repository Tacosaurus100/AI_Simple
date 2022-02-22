#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <string>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

using namespace std;

namespace chess {
   class Piece : public wxStaticBitmap{
      public: 
         Piece(wxBitmap* bitmap, wxWindow* parent, int id, const std::string position, const bool isWhite, const std::string name);
         Piece(const std::string position, const bool isWhite, const std::string name);

         ~Piece();

         void reparent (wxThreadEvent& event);

         void onClick();
         void clickNoGUI(wxWindow* board);

         std::string move(std::string position, bool isCapture);
         void highlight();
         void unhighlight();

         std::string position;
         bool isWhite;
         std::string name;
         bool moved;
         int validMoveCount;
         
         const wxColor* color = new wxColor (220, 20, 20, 255);
   };
}

#endif