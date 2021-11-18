#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP
#define WINDOW_ID 3
#define BORDER_WIDTH 15
#define BOX_WIDTH 80

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <chess/Piece.hpp>
#include <chess/Square.hpp>
#include <chess/PlayerWhite.hpp>
#include <chess/PlayerBlack.hpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

using namespace std;

namespace chess {
   class Board : public wxFrame{
      public: 
         Board ();

         Board(const wxString& title, const wxPoint& pos, const wxSize& size);

         std::string confirmMove (Piece* piece, std::string pos);

         std::string move (std::string pos, Piece* piece = nullptr);
         std::string moveHelper (std::string pos, Piece* piece = nullptr);

         void unhighlight();

         wxPanel* getSquare (int i, int j);

         wxPanel* getSquare (std::string pos);

         static void init (Board* frame);

         void OnClick ();

         bool isValidMove (Piece* piece, std::string pos, bool check = true);


         bool checkPawnForward (Piece* piece, std::string pos);
         bool pawnCapture (Piece* piece, std::string pos, bool enact = true);
         bool checkKnight (int* first, int* second);
         bool checkDiagonal (int* first, int* second);
         bool checkStraight (int* first, int* second);
         bool checkKing (Piece* piece, std::string pos);

         bool causesCheck (Piece* piece, std::string pos);
         bool isInCheck (Piece* piece);

         bool checkmate ();

         bool stalemate ();
   


         Square*** squares;
         Piece* activePiece;
         bool isWhitesTurn;
         std::string prevMove;
         PlayerWhite* pw;
         PlayerBlack* pb;
         wxFrame* promotionMenu;
         bool promotionMenuIsActive;
   };
}

#endif