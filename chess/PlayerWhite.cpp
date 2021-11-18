#ifndef CHESS_PLAYER_WHITE_CPP
#define CHESS_PLAYER_WHITE_CPP


#include <chess/Piece.cpp>
#include <chess/PlayerWhite.hpp>
#include <chess/Player.cpp>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>

PlayerWhite::PlayerWhite(Square*** squares) {
   const int PLAYER_WHITE_ID = 200;
   pieces = new Piece* [16];

   string* currentPath = new string (filesystem::current_path());
   // std::cout << *currentPath + "/Chess_Pieces/White_Pawn.png";

   wxBitmap* newBitmap;
   wxImage* img;
   img = new wxImage(*currentPath + "/Chess_Pieces/White_Pawn.png", wxBITMAP_TYPE_PNG);
   img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
   newBitmap = new wxBitmap (*img);
   // std::cout << board->parsePos ("h2")[0];
   // exit (0);
   pieces[0] = new Piece (newBitmap, Square::getSquare(squares, "a2"), PLAYER_WHITE_ID + 0, "a2", true, "pawn");
   pieces[1] = new Piece (newBitmap, Square::getSquare(squares, "b2"), PLAYER_WHITE_ID + 1, "b2", true, "pawn");
   pieces[2] = new Piece (newBitmap, Square::getSquare(squares, "c2"), PLAYER_WHITE_ID + 2, "c2", true, "pawn");
   pieces[3] = new Piece (newBitmap, Square::getSquare(squares, "d2"), PLAYER_WHITE_ID + 3, "d2", true, "pawn");
   pieces[4] = new Piece (newBitmap, Square::getSquare(squares, "e2"), PLAYER_WHITE_ID + 4, "e2", true, "pawn");
   pieces[5] = new Piece (newBitmap, Square::getSquare(squares, "f2"), PLAYER_WHITE_ID + 5, "f2", true, "pawn");
   pieces[6] = new Piece (newBitmap, Square::getSquare(squares, "g2"), PLAYER_WHITE_ID + 6, "g2", true, "pawn");
   pieces[7] = new Piece (newBitmap, Square::getSquare(squares, "h2"), PLAYER_WHITE_ID + 7, "h2", true, "pawn");

   img = new wxImage(*currentPath + "/Chess_Pieces/White_Rook.png", wxBITMAP_TYPE_PNG);
   img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
   newBitmap = new wxBitmap (*img);
   pieces[8] = new Piece (newBitmap, Square::getSquare(squares, "a1"), PLAYER_WHITE_ID + 8, "a1", true, "rook"); 
   pieces[9] = new Piece (newBitmap, Square::getSquare(squares, "h1"), PLAYER_WHITE_ID + 9, "h1", true, "rook");

   img = new wxImage(*currentPath + "/Chess_Pieces/White_Knight.png", wxBITMAP_TYPE_PNG);
   img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
   newBitmap = new wxBitmap (*img);
   pieces[10] = new Piece (newBitmap, Square::getSquare(squares, "b1"), PLAYER_WHITE_ID + 10, "b1", true, "knight"); 
   pieces[11] = new Piece (newBitmap, Square::getSquare(squares, "g1"), PLAYER_WHITE_ID + 11, "g1", true, "knight");

   img = new wxImage(*currentPath + "/Chess_Pieces/White_Bishop.png", wxBITMAP_TYPE_PNG);
   img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
   newBitmap = new wxBitmap (*img);
   pieces[12] = new Piece (newBitmap, Square::getSquare(squares, "c1"), PLAYER_WHITE_ID + 12, "c1", true, "bishop"); 
   pieces[13] = new Piece (newBitmap, Square::getSquare(squares, "f1"), PLAYER_WHITE_ID + 13, "f1", true, "bishop");

   img = new wxImage(*currentPath + "/Chess_Pieces/White_Queen.png", wxBITMAP_TYPE_PNG);
   img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
   newBitmap = new wxBitmap (*img);
   pieces[14] = new Piece (newBitmap, Square::getSquare(squares, "d1"), PLAYER_WHITE_ID + 14, "d1", true, "queen");

   img = new wxImage(*currentPath + "/Chess_Pieces/White_King.png", wxBITMAP_TYPE_PNG);
   img->Rescale (BOX_WIDTH + 2, BOX_WIDTH);
   newBitmap = new wxBitmap (*img);
   pieces[15] = new Piece (newBitmap, Square::getSquare(squares, "e1"), PLAYER_WHITE_ID + 15, "e1", true, "king");
}

#endif