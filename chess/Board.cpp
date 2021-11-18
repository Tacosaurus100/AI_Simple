#ifndef CHESS_BOARD_CPP
#define CHESS_BOARD_CPP

#include <chess/Board.hpp>
#include <chess/PromotionMenu.hpp>
#include <chess/Square.cpp>
#include <cmath>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
 
using namespace chess;

Board::Board(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame*)NULL, WINDOW_ID, title, pos, size)
{
   activePiece = nullptr;
   isWhitesTurn = true;
   this->pw = nullptr;
   this->pb = nullptr;
   promotionMenuIsActive = false;
}

void Board::init(Board* frame) {
   const int SQUARE_ID = 20;
   wxPoint* point = new wxPoint (-1, -1);
   wxSize* minSize = new wxSize (BORDER_WIDTH * 2 + BOX_WIDTH * 8, BORDER_WIDTH * 2 + BOX_WIDTH * 8);

   frame->SetMinClientSize (*minSize);
   frame->SetMaxClientSize (*minSize);
// (wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, std::string position)
   wxPoint* boxPoint;
   wxSize* boxSize = new wxSize (BOX_WIDTH, BOX_WIDTH);
   frame->squares = new Square** [8];
   for (int i = 0; i < 8; i++) {
      frame->squares[i] = new Square* [8];
      for (int j = 0; j < 8; j++) {
         boxPoint = new wxPoint (BORDER_WIDTH + BOX_WIDTH * i + 4, BORDER_WIDTH + BOX_WIDTH * j);
         frame->squares[i][j] = new Square(frame, SQUARE_ID + i * 8 + j, *boxPoint, *boxSize, std::string(1, (char) (i + 97)) + (char) (7 + 49 - j));
         frame->squares[i][j]->SetBackgroundColour((i + j) % 2 == 0 ? wxColour(* wxWHITE) : wxColour(* wxBLUE));
      }
   }
}

void Board::unhighlight() { 
   for (int i = 0; i < 16; i++) {
      if (pw->pieces[i] != nullptr) {
         pw->pieces[i]->unhighlight();
      }
      if (pb->pieces[i] != nullptr) {
         pb->pieces[i]->unhighlight();
      }
   }
} 

wxPanel* Board::getSquare (int i, int j) {
   return squares[i][j];
}

wxPanel* Board::getSquare (std::string pos) {
   return Square::getSquare(squares, pos);
}

std::string Board::confirmMove (Piece* piece, std::string pos) {
   this->prevMove = piece->move (pos);
   piece->Reparent(this->getSquare (pos));
   this->Update();
   activePiece = nullptr;
   isWhitesTurn = !isWhitesTurn;
   return pos;
}

std::string Board::moveHelper (std::string pos, Piece* piece) {
   std::string output = "";
   if (!promotionMenuIsActive) {
      output = move (pos, piece);
      if (output != "") {
         if (stalemate ()) {
            if (this->isWhitesTurn) {
               if (isInCheck(pw->pieces[15])) {
                  std::cout << "Black Won!" << '\n';
               } else {
                  std::cout << "Black Stalemated White!" << '\n';
               }
            } else {
               if (isInCheck(pb->pieces[15])) {
                  std::cout << "White Won!" << '\n';
               } else {
                  std::cout << "White Stalemated Black!" << '\n';
               }
            }
         }
      }
   }

   if (this->prevMove.length() == 2 && output != "") {
      int* arr = Square::parsePos (this->prevMove);
      if (arr[1] == 0) {
         this->promotionMenuIsActive = true;
         ((PromotionMenu*) this->promotionMenu)->show(false);
      } else if (arr[1] == 7) {
         std::cout << this->prevMove;
         this->promotionMenuIsActive = true;
         ((PromotionMenu*) this->promotionMenu)->show(true);
      }
      delete[] arr;
   }
   return output;
}

std::string Board::move (std::string pos, Piece* piece){
   if (piece != nullptr) {
      // clicked a different piece on same team
      if (piece->isWhite == this->isWhitesTurn) {
         activePiece = piece;
      }
      // clicked a different piece on enemy team 
      else if (activePiece != nullptr) {
         if (isValidMove (activePiece, pos)) {
            std::cout << "here\n";
            pw->removePiece(pos);
            pb->removePiece(pos);

            if (activePiece->name == "pawn") {
               pawnCapture (activePiece, pos);
               return pos;
            } else {
            
               this->getSquare(pos)->DestroyChildren ();//this->getSquare (pos)->GetChildren()->IndexOf(0);
               std::string output = confirmMove(activePiece, pos);

               std::cout << std::string(1, this->prevMove[0]) << "x" << this->prevMove[1] << this->prevMove[2] << ' ';
               if (isWhitesTurn) {
                  std::cout << '\n';
               }
               unhighlight();
               return output;
            }
         }
      }
   } else if (activePiece != nullptr) {
      if (isValidMove (activePiece, pos)) {
         if (activePiece->name == "pawn") {
            std::string initial = activePiece->position;
            if (pawnCapture (activePiece, pos)) {
               return std::string(1, initial[0]) + "x" + pos;
            }
         }
         std::string output = confirmMove(activePiece, pos);
         std::cout << this->prevMove << ' ';
         if (isWhitesTurn) {
            std::cout << '\n';
         }
         return output;
      }
   }
   return "";
}


// checks to see if the move can be made, does not include taking pieces 
bool Board::isValidMove (Piece* piece, std::string pos, bool check) {
   int* first = Square::parsePos(piece->position);
   int* second = Square::parsePos(pos);
   bool val = false;

   if (check && causesCheck(piece, pos)) {
      val = false;
   } else if (piece->name == "pawn") {
      val = checkPawnForward(piece, pos) || pawnCapture(piece, pos, false);
   } else if (piece->name == "knight") {
      val = checkKnight (first, second);
   } else if (piece->name == "bishop") {
      val = checkDiagonal (first, second);
   } else if (piece->name == "rook") {
      val = checkStraight (first, second);
   } else if (piece->name == "queen") {
      val = checkDiagonal (first, second) || checkStraight (first, second);
   } else if (piece->name == "king") {
      val = checkKing (piece, pos);   
   }
   delete[] first;
   delete[] second;
   return val;
}

bool Board::checkPawnForward (Piece* piece, std::string pos) {
   int* second = Square::parsePos(pos);
   int* first = Square::parsePos(piece->position);
   int multiplier = 1;
   if (piece->isWhite) {
      multiplier = -1;
   }
   bool val = false;

   if (!piece->moved) { 
      if ((first[0] == second[0] && first[1] + 1 * multiplier == second[1]) && 
         (this->getSquare(first[0], first[1] + 1 * multiplier)->GetChildren().size() == 0)) {
            val = true;
         }
      else if ((first[0] == second[0] && first[1] + 2 * multiplier == second[1]) && 
         (this->getSquare(first[0], first[1] + 1 * multiplier)->GetChildren().size() == 0 && 
         this->getSquare(first[0], first[1] + 2 * multiplier)->GetChildren().size() == 0)) {
            val = true;
         }
   }
   else if (first[0] == second[0] && first[1] + 1 * multiplier == second[1] && 
            this->getSquare(first[0], first[1] + 1 * multiplier)->GetChildren().size() == 0) {
      val = true;
   }
   delete[] first;
   delete[] second;
   return val;
}

bool Board::pawnCapture (Piece* piece, std::string pos, bool enact) {
   int* first = Square::parsePos(piece->position);
   int* second = Square::parsePos(pos);
   bool val = false;
   int multiplier = 1;
   if (piece->isWhite) {
      multiplier = -1;
   }

   if (first[0] == second[0]) {
      val = false;
   }

   //e4xd5 || e4xf5
   else if ((first[0] + 1 == second[0] || first[0] - 1 == second[0]) && first[1] + multiplier == second[1]) {
      // if square is empty
      if (this->getSquare(second[0], second[1])->GetChildren().IsEmpty()) {
         // check for en passant

         Piece* adjPiece = (Piece*) this->getSquare(second[0], second[1] - multiplier)->GetChildren().front();
         if (this->getSquare(second[0], second[1] - multiplier)->GetChildren().GetCount() == 0) {
            val = false;
         }
         
         else if (adjPiece->isWhite != piece->isWhite && adjPiece->name == "pawn") {
            if (pos[0] == adjPiece->position[0]) {
               if (piece->isWhite) {
                  if (pos[1] == '6') {
                     if (this->prevMove[0] == pos[0] && std::strcmp(&this->prevMove[1], "5") == 0) {
                        if (enact) {
                           this->getSquare(adjPiece->position)->DestroyChildren ();
                           confirmMove(piece, pos);
                        }
                        val = true;
                     }
                  }
               } else {
                  if (pos[1] == '3') {
                     if (this->prevMove[0] == pos[0] && std::strcmp(&this->prevMove[1], "4") == 0) {
                        if (enact) {
                           this->getSquare(adjPiece->position)->DestroyChildren ();
                           confirmMove(piece, pos);
                        }
                        val = true;
                     }
                  }
               }
            }
         } else {
            val = false;
         }
      } 
      
      // regular capture
      else {
         if (enact) { 
            std::cout << piece->position[0] << "x" << pos << ' ';
            if (!isWhitesTurn) {
               std::cout << '\n';
            }
            this->getSquare(pos)->DestroyChildren ();
            confirmMove (piece, pos);
         } 
         val = true;
      }
   }
   delete[] first;
   delete[] second;
   return val;
}

bool Board::checkKnight (int* first, int* second) {
   if (first[0] == second[0] || first[1] == second[1]) {
      return false;
   }
   if (std::abs(first[0] - second[0]) + std::abs(first[1] - second[1]) != 3) {
      return false;
   }
   return true;
}

bool Board::checkDiagonal (int* first, int* second) {
   // the same column
   if (first[0] + first[1] == second[0] + second[1]) {
      int multiplier = -1;
      if (second[1] > first[1]) {
         multiplier = 1;
      }
      //b5-f1
      //f1-b5
      //5
      for (int i = 1; i < std::abs(first[0] - second[0]); i++) {
         if (this->getSquare(second[0] + i * multiplier, second[1] - i * multiplier)->GetChildren().size() != 0) {
            return false;
         }
      }
      return true;
   } else if (second[0] - first[0] == second[1] - first[1]) { 
      //h3-f1
      //f1-h3
      int multiplier = -1;
      if (second[1] > first[1]) {
         multiplier = 1;
      }
      for (int i = 1; i < std::abs(first[0] - second[0]); i++) {
         if (this->getSquare(second[0] - i * multiplier, second[1] - i * multiplier)->GetChildren().size() != 0) {
            return false;
         }
      }
      return true;
   }

   //d4-d6
   return false;
}

bool Board::checkStraight (int* first, int* second) {
   // the same column
   if (first[0] != second[0] && first[1] != second[1]) {
      return false;
   }
   if (first[0] == second[0]) {
      int multiplier = -1;
      if (second[1] > first[1]) {
         multiplier = 1;
      }
      for (int i = 0; i < std::abs(second[1] - first[1]) - 1; i++) {
         if (this->getSquare(first[0], (i + 1) * multiplier + first[1])->GetChildren().size() != 0) {
            return false;
         }
      }
   } 
   // same column
   else {
      int multiplier = -1;
      if (second[0] > first[0]) {
         multiplier = 1;
      }
      for (int i = 0; i < std::abs(second[0] - first[0]) - 1; i++) {
         if (this->getSquare(first[0] + (i + 1) * multiplier, first[1])->GetChildren().size() != 0) {
            return false;
         }
      }
   }

   return true;
}

bool Board::checkKing (Piece* piece, std::string pos) {
   int* first = Square::parsePos(piece->position);
   int* second = Square::parsePos(pos);
   bool val = false;
   Piece* active = this->activePiece;
   if (this->getSquare(second[0], second[1])->GetChildren().size() != 0 &&
      ((Piece*) this->getSquare(second[0], second[1])->GetChildren().front())->isWhite == piece->isWhite) {
         val = false;
      }
   else if (std::abs(first[0] - second[0]) + std::abs(first[1] - second[1]) == 1) {
      // confirmMove (piece, pos);
      val = true;
   }

   else if (std::abs(first[0] - second[0]) + std::abs(first[1] - second[1]) == 2) {
      if ((first[0] == second[0] || first[1] == second[1]) && piece->moved) {
         val = false;
      }
      else if (first[0] != second[0] && first[1] != second[1]) {
         // confirmMove (piece, pos);
         val = true;
      }

      // castle options
      else if (!piece->moved && !isInCheck(piece)){
         // castle queen-side
         if (first[0] - second[0] > 0) {
            std::string rookPlacement = "d";
            rookPlacement.push_back((char) piece->position[1]);
            std::string check = "b";
            check.push_back((char) piece->position[1]);

            Piece* rook;
            if (this->isWhitesTurn) {
               rook = pw->pieces[8];
            } else {
               rook = pb->pieces[8];
            }
            int* arr = Square::parsePos(check);
            if (checkStraight (first, arr)) {
               if (rook != nullptr && !rook->moved) {

                  std::cout << "straight\n";
                  if (!causesCheck (piece, rookPlacement) && !causesCheck (piece, pos)) {
                     std::cout << "O-O-O ";
                     if (isWhitesTurn) {
                        std::cout << '\n';
                     }
                     confirmMove (rook, rookPlacement);
                     isWhitesTurn = !isWhitesTurn;
                     unhighlight();
                     val = true;
                  }
               }
            }
            delete[] arr;
         }
         // castle king-side
         else {
            std::string rookPlacement = "f";
            rookPlacement.push_back((char) piece->position[1]);
            std::string check = "g";
            check.push_back((char) piece->position[1]);

            Piece* rook;
            if (this->isWhitesTurn) {
               rook = this->pw->pieces[9];
            } else {
               rook = this->pb->pieces[9];
            }

            int* arr = Square::parsePos(check);
            if (checkStraight (first, arr)) {
               if (rook != nullptr && !rook->moved) {
                  if (!causesCheck (piece, rookPlacement) && !causesCheck (piece, pos)) {
                     std::cout << "O-O ";
                     if (isWhitesTurn) {
                        std::cout << '\n';
                     }
                     confirmMove (rook, rookPlacement);
                     isWhitesTurn = !isWhitesTurn;
                     val = true;
                  }
               }
            }
            delete[] arr;
         }
      }
   }
   this->activePiece = active;
   delete[] first;
   delete[] second;
   return val;
}

// needs to pretend that the piece has moved to the location and search to see if king is now in check.

// move it, check to see if valid, move it back, return true/false
bool Board::causesCheck (Piece* piece, std::string pos) {
   std::string initialpos = piece->position;
   bool initialMoved = piece->moved;
   Piece* activePiece = this->activePiece;
   std::string prev = this->prevMove;
   confirmMove (piece, pos);
   this->isWhitesTurn = !this->isWhitesTurn;
   bool causesCheck = isInCheck (activePiece);
   confirmMove (piece, initialpos);
   this->isWhitesTurn = !this->isWhitesTurn;
   piece->moved = initialMoved;
   this->activePiece = activePiece;
   this->prevMove = prev;
   return causesCheck;
}

bool Board::isInCheck (Piece* piece) {
   std::string prev = this->prevMove;
   Player* current;
   Player* next;
   if (this->isWhitesTurn) {
      current = pw;
      next = pb;
   } else {
      current = pb;
      next = pw;
   }
   Piece* currentKing = current->pieces[15];
   for (int i = 0; i < 16; i++) {
      Piece* nextPiece = next->pieces[i];
      if (nextPiece != nullptr) {
         if (piece->position != nextPiece->position) {
            if (isValidMove(nextPiece, currentKing->position, false)) {
               this->prevMove = prev;
               return true;
            }
         } 
      }
   }
   this->prevMove = prev;
   return false;
}

// if is in stalemate but also currently in check
bool Board::checkmate () {
   if (this->isWhitesTurn) {
      if (!isInCheck(pw->pieces[15])) {
         return false;
      }
   } else {
      if (!isInCheck(pb->pieces[15])) {
         return false;
      }
   }

   return stalemate();
}


bool Board::stalemate () {
   std::string prev = this->prevMove;
   Piece* activePiece = this->activePiece;
   Player* current;
   Player* next;
   if (!this->isWhitesTurn) {
      current = pw;
      next = pb;
   } else {
      current = pb;
      next = pw;
   }
   Piece* currentKing = current->pieces[15];
   for (int i = 0; i < 16; i++) {
      Piece* nextPiece = next->pieces[i];
      if (nextPiece != nullptr) {

         for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
               std::string posToCheck = std::string (1, (char) ('a' + j));
               posToCheck.push_back((char) ('0' + k + 1));
               this->activePiece = nextPiece;
               if (isValidMove(nextPiece, posToCheck)) {
                  this->activePiece = activePiece;
                  this->prevMove = prev;
                  return false;
               }
            }
         }
      }   
   }
   
   this->activePiece = activePiece;
   this->prevMove = prev;
   return true;
}

#endif