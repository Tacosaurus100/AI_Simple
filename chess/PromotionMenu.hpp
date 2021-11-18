#ifndef CHESS_PROMOTION_MENU_HPP
#define CHESS_PROMOTION_MENU_HPP

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <chess/PromotionPiece.hpp>
#include <chess/Square.hpp>
#include <chess/PlayerWhite.hpp>
#include <chess/PlayerBlack.hpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

using namespace std;

namespace chess {
   class PromotionMenu : public wxFrame{
      public:
         PromotionMenu(const wxString& title, const wxPoint& pos, const wxSize& size);

         Square*** squares;
         static void init (PromotionMenu* frame);

         void promote (PromotionPiece* piece);
         void show (bool isWhite);
      
         wxFrame* board;

         PromotionPiece** pieces;
   };
}

#endif