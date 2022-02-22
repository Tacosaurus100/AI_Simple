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

         std::string confirmMove (Piece* piece, std::string pos, bool destroy = true);

         std::string move (std::string pos, Piece* piece = nullptr);
         std::string moveHelper (std::string pos, Piece* piece = nullptr);

         void unhighlight();

         wxPanel* getSquare (int i, int j);

         wxPanel* getSquare (std::string pos);

         void reparent (wxThreadEvent& event);

         static void init (Board* frame);

         void OnClick ();

         bool isValidMove (Piece* piece, std::string pos, bool check = true);

         bool pieceAtPosition (std::string position, bool isWhite);

         bool pieceAtPositionEither (int first, int second);

         Piece* getPieceAt (int first, int second);

         bool checkPawnForward (Piece* piece, std::string pos);
         bool pawnCapture (Piece* piece, std::string pos, bool enact = true);
         bool checkKnight (int* first, int* second);
         bool checkDiagonal (int* first, int* second);
         bool checkStraight (int* first, int* second);
         bool checkKing (Piece* piece, std::string pos, bool enact = false);

         bool causesCheck (Piece* piece, std::string pos);
         Piece* isInCheck ();

         bool checkmate ();

         bool stalemate ();
         bool enoughPiecesToWin ();

         std::string* getValidMoves(Piece* piece);

         Square*** squares;
         Piece* activePiece;
         bool isWhitesTurn;
         std::string prevMove;
         bool canEnpassant;
         PlayerWhite* pw;
         PlayerBlack* pb;
         wxFrame* promotionMenu;
         bool promotionMenuIsActive;

         // -1 is black won, 1 is white won, -0.1 is white stalemated black (shouldve won but didnt) and 0.1 is black stalemated white
         double gameOver;
   };
}

#endif