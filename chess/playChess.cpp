#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <sys/time.h>
#include <sys/resource.h>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

#include "playChess.hpp"

#include <chess/Board.cpp>
#include <chess/PromotionMenu.cpp>
#include <chess/Piece.cpp>
#include <chess/PlayerWhite.cpp>
#include <chess/PlayerBlack.cpp>

using namespace chess;
using namespace std;

IMPLEMENT_APP(PlayChess)
bool PlayChess::OnInit() {
   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../../chess";
   filesystem::current_path(filesystem::path(*currentPath));
   wxInitAllImageHandlers();
   
   Board* board = new Board(wxT("Chess"), wxPoint(-1,-1), wxSize(670,698));
   Board::init (board);

   PromotionMenu* promotionMenu = new PromotionMenu(wxT("Promotion"), wxPoint(-1,-1), wxSize(190,218));
   PromotionMenu::init (promotionMenu);

   board->pb = new PlayerBlack (board->squares);
   board->pw = new PlayerWhite (board->squares);
   board->promotionMenu = promotionMenu;
   promotionMenu->board = board;

   // Connect(WINDOW_ID, wxEVT_LEAVE_WINDOW, (wxObjectEventFunction) &Board::OnClick);
   board->Show(true);
   // SetTopWindow(promotionMenu);
   return true;
}



