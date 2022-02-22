#ifndef CHESS_PLAYER_BLACK_CPP
#define CHESS_PLAYER_BLACK_CPP

// #define PLAYER_BLACK_ID 100;

#include <chess/Piece.cpp>
#include <chess/PlayerBlack.hpp>
#include <chess/Player.cpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

PlayerBlack::PlayerBlack(Square*** squares) {
   const int PLAYER_BLACK_ID = 100;
   pieces = new Piece* [16];

   string* currentPath = new string (filesystem::current_path());
   // std::cout << *currentPath + "/Chess_Pieces/Black_Pawn.png";

   wxBitmap* newBitmap;
   wxImage* img;
   if (GUI) {
      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Pawn.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      // std::cout << board->parsePos ("h7")[0];
      // exit (0);
      pieces[0] = new Piece (newBitmap, Square::getSquare(squares, "a7"), PLAYER_BLACK_ID + 0, "a7", false, "pawn");
      pieces[1] = new Piece (newBitmap, Square::getSquare(squares, "b7"), PLAYER_BLACK_ID + 1, "b7", false, "pawn");
      pieces[2] = new Piece (newBitmap, Square::getSquare(squares, "c7"), PLAYER_BLACK_ID + 2, "c7", false, "pawn");
      pieces[3] = new Piece (newBitmap, Square::getSquare(squares, "d7"), PLAYER_BLACK_ID + 3, "d7", false, "pawn");
      pieces[4] = new Piece (newBitmap, Square::getSquare(squares, "e7"), PLAYER_BLACK_ID + 4, "e7", false, "pawn");
      pieces[5] = new Piece (newBitmap, Square::getSquare(squares, "f7"), PLAYER_BLACK_ID + 5, "f7", false, "pawn");
      pieces[6] = new Piece (newBitmap, Square::getSquare(squares, "g7"), PLAYER_BLACK_ID + 6, "g7", false, "pawn");
      pieces[7] = new Piece (newBitmap, Square::getSquare(squares, "h7"), PLAYER_BLACK_ID + 7, "h7", false, "pawn");

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Rook.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      pieces[8] = new Piece (newBitmap, Square::getSquare(squares, "a8"), PLAYER_BLACK_ID + 8, "a8", false, "rook"); 
      pieces[9] = new Piece (newBitmap, Square::getSquare(squares, "h8"), PLAYER_BLACK_ID + 9, "h8", false, "rook");

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Knight.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      pieces[10] = new Piece (newBitmap, Square::getSquare(squares, "b8"), PLAYER_BLACK_ID + 10, "b8", false, "knight"); 
      pieces[11] = new Piece (newBitmap, Square::getSquare(squares, "g8"), PLAYER_BLACK_ID + 11, "g8", false, "knight");

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Bishop.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      pieces[12] = new Piece (newBitmap, Square::getSquare(squares, "c8"), PLAYER_BLACK_ID + 12,  "c8", false, "bishop"); 
      pieces[13] = new Piece (newBitmap, Square::getSquare(squares, "f8"), PLAYER_BLACK_ID + 13, "f8", false, "bishop");

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_Queen.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      pieces[14] = new Piece (newBitmap, Square::getSquare(squares, "d8"), PLAYER_BLACK_ID + 14, "d8", false, "queen");

      img = new wxImage(*currentPath + "/Chess_Pieces/Black_King.png", wxBITMAP_TYPE_PNG);
      img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
      newBitmap = new wxBitmap (*img);
      pieces[15] = new Piece (newBitmap, Square::getSquare(squares, "e8"), PLAYER_BLACK_ID + 15, "e8", false, "king");
   } else {
      pieces[0] = new Piece ("a7", false, "pawn");
      pieces[1] = new Piece ("b7", false, "pawn");
      pieces[2] = new Piece ("c7", false, "pawn");
      pieces[3] = new Piece ("d7", false, "pawn");
      pieces[4] = new Piece ("e7", false, "pawn");
      pieces[5] = new Piece ("f7", false, "pawn");
      pieces[6] = new Piece ("g7", false, "pawn");
      pieces[7] = new Piece ("h7", false, "pawn");
      pieces[8] = new Piece ("a8", false, "rook"); 
      pieces[9] = new Piece ("h8", false, "rook");
      pieces[10] = new Piece ("b8", false, "knight"); 
      pieces[11] = new Piece ("g8", false, "knight");
      pieces[12] = new Piece ("c8", false, "bishop"); 
      pieces[13] = new Piece ("f8", false, "bishop");
      pieces[14] = new Piece ("d8", false, "queen");
      pieces[15] = new Piece ("e8", false, "king");
   }
}

#endif