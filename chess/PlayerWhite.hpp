#ifndef CHESS_PLAYER_WHITE_HPP
#define CHESS_PLAYER_WHITE_HPP

#include <chess/Player.hpp>
#include <chess/Piece.hpp>

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

namespace chess {
   class PlayerWhite : public chess::Player{
      public:
         PlayerWhite (Square*** squares);
   };
}

#endif