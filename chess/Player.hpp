#ifndef CHESS_PLAYER_HPP
#define CHESS_PLAYER_HPP

#include <string>
#include <chess/Piece.hpp>
#include <chess/Square.hpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

using namespace chess;

namespace chess {
   class Player {
      public:
         void move (std::string command);

         Piece** pieces;

         void removePiece (std::string pos);
      private:

   };
}




#endif