#ifndef CHESS_PROMOTION_PIECE_HPP
#define CHESS_PROMOTION_PIECE_HPP

#include <string>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

using namespace std;

namespace chess {
   class PromotionPiece : public wxStaticBitmap{
      public: 
         PromotionPiece(wxBitmap* bitmap, wxWindow* parent, int id, const bool isWhite, const std::string name);

         PromotionPiece(const bool isWhite, const std::string name);

         void onClick();
         
         bool isWhite;
         std::string name;
   };
}

#endif