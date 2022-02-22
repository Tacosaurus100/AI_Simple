#ifndef CHESS_BOARD_CPP
#define CHESS_BOARD_CPP

#include <chess/Board.hpp>
#include <chess/PromotionMenu.hpp>
#include <chess/Square.cpp>
#include <cmath>

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/gdicmn.h>
#include <wx/utils.h>
 
using namespace chess;

Board::Board(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame*)NULL, WINDOW_ID, title, pos, size)
{
   this->activePiece = nullptr;
   this->isWhitesTurn = true;
   this->pw = nullptr;
   this->pb = nullptr;
   this->promotionMenuIsActive = false;
   this->gameOver = 0;
   this->canEnpassant = false;
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
         if (GUI) {
            frame->squares[i][j] = new Square(frame, SQUARE_ID + i * 8 + j, *boxPoint, *boxSize, std::string(1, (char) (i + 97)) + (char) (7 + 49 - j));
            frame->squares[i][j]->SetBackgroundColour((i + j) % 2 == 0 ? wxColour(* wxWHITE) : wxColour(* wxBLUE));
         } else {
            frame->squares[i][j] = new Square(std::string(1, (char) (i + 97)) + (char) (7 + 49 - j));
         }
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

void Board::reparent (wxThreadEvent& event) {
   // std::cout << "\nspace to delete" << finalPos.substr(2, 2) << '\n';
   // std::cout << "\nspace to move" << finalPos.substr(0, 2) << '\n';
   // std::cout << "\nspace to delete" << finalPos.substr(0, 2) << '\n';
   // int* parsed = Square::parsePos(finalPos.substr(0, 2));
   // std::cout << "reparent " << event.GetExtraLong() << " to " << event.GetString().ToStdString() << "\n";
   Piece* piece = ((Piece*) wxWindow::FindWindowById(event.GetExtraLong()));
   std::string finalPos = event.GetString().ToStdString();
   int* parsed = Square::parsePos(finalPos);


   // std::cout << "is main " << wxThread::IsMain () << '\n';
   if (piece == nullptr) {
      std::cout << "error\n";
      Player* current = !isWhitesTurn ? (Player*) this->pw : (Player*) this->pb;
      for (int i = 0; i < 16; i++) {
         if (current->pieces[i] != nullptr) {
            std::cout << current->pieces[i]->name << " " << current->pieces[i]->position << '\n';
         }
      }
   } 

   // Player* current = !isWhitesTurn ? (Player*) this->pw : (Player*) this->pb;
   // for (int i = 0; i < 16; i++) {
   //    if (current->pieces[i] != nullptr) {
   //       std::cout << current->pieces[i]->name << " " << current->pieces[i]->position << '\n';
   //    }
   // }

   if (this->getSquare(parsed[0], parsed[1]) == nullptr) {
      std::cout << "error2\n";
   } 
   if (wxThread::IsMain () == 0) {
      // if (wxTheApp->HasPendingEvents()) { 
      //    wxTheApp->ProcessPendingEvents();
      // }
      // wxThreadEvent evt1(wxEVT_COMBOBOX, WINDOW_ID);
      // evt1.SetString(event.GetString());
      // evt1.SetExtraLong(event.GetExtraLong());

      std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));
      wxTheApp->QueueEvent(event.Clone());
      std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));
   } else if (wxThread::IsMain () != 0) {
      std::cout << "space to move from " << piece->position << '\n';
      std::cout << "space to move from " << piece->name << " " << piece->position << '\n';

      std::cout << ((Square*) this->getSquare(finalPos))->position << '\n';

      std::cout << parsed[0] << parsed[1] << '\n';
      wxWindow* parent = this->getSquare(parsed[0], parsed[1]);
      if (piece == nullptr) {
         std::cout << "error3\n";
      }

      this->getSquare(finalPos)->DestroyChildren();
      piece->Reparent ((parent));
      unhighlight();
   }
   delete parsed;
}

bool Board::pieceAtPosition (std::string position, bool isWhite) {
   Player* current = isWhite ? (Player*) this->pw : (Player*) this->pb;
   for (int i = 0; i < 16; i++) {
      if (current->pieces[i] != nullptr) {
         if (current->pieces[i]->position == position) {
            return true;
         }
      }
   }
   return false;
}

bool Board::pieceAtPositionEither (int first, int second) {
   int* parsed;
   for (int i = 0; i < 16; i++) {
      if (this->pw->pieces[i] != nullptr) {
         parsed = Square::parsePos(this->pw->pieces[i]->position);
         if (parsed[0] == first && parsed[1] == second) {
            delete parsed;
            return true;
         }
         delete parsed;
      }

      if (this->pb->pieces[i] != nullptr) {
         parsed = Square::parsePos(this->pb->pieces[i]->position);
         if (parsed[0] == first && parsed[1] == second) {
            delete parsed;
            return true;
         }
         delete parsed;
      }
   }
   return false;
}

Piece* Board::getPieceAt (int first, int second) {
   int* parsed;
   for (int i = 0; i < 16; i++) {

      if (this->pw->pieces[i] != nullptr) {
         parsed = Square::parsePos(this->pw->pieces[i]->position);
         if (parsed[0] == first && parsed[1] == second) {
            delete parsed;
            return this->pw->pieces[i];
         }
         delete parsed;
      }

      if (this->pb->pieces[i] != nullptr) {
         parsed = Square::parsePos(this->pb->pieces[i]->position);
         if (parsed[0] == first && parsed[1] == second) {
            delete parsed;
            return this->pb->pieces[i];
         }
         delete parsed;
      }
   }
   return nullptr;
}

std::string Board::confirmMove (Piece* piece, std::string pos, bool destroy) {
   std::string initialPos = piece->position;
   bool initialMoved = piece->moved;
   std::string move = "";
   if (initialPos == pos) {
      return "";
   }
   if (pieceAtPosition (pos, this->isWhitesTurn)) {
      return "";
   }
   if (destroy && piece->isWhite != this->isWhitesTurn) {
      return "";
   }
   bool isEmpty = false;

   // kill the piece at the position to move to
   if (destroy) {
      isEmpty = pw->removePiece(pos) || pb->removePiece(pos);
      activePiece = nullptr;
      isWhitesTurn = !isWhitesTurn;
      canEnpassant = false;
   }

   // make the move
   move = piece->move (pos, isEmpty);
   // move = "";
   if (destroy) {

      // if (wxTheApp->HasPendingEvents()) { 
      //    wxTheApp->ProcessPendingEvents();
      // }

      // wxThreadEvent evt3( wxEVT_COMBOBOX_CLOSEUP, wxID_ANY);
      // wxTheApp->QueueEvent (evt3.Clone());
      // std::this_thread::sleep_for (std::chrono::microseconds(SLEEP_TIME));

      this->prevMove = move;
      std::cout << move;
      if (isInCheck()) {
         std::cout << "+";
      }
      std::cout << " ";
      if (isWhitesTurn) {
         std::cout << '\n';
      }

      if (GUI) {
         wxThreadEvent evt1(wxEVT_COMBOBOX, WINDOW_ID);
         int* parsed = Square::parsePos(initialPos);
         wxString str(pos);
         delete parsed;
         evt1.SetString(str);
         evt1.SetExtraLong(piece->GetId());
         wxTheApp->QueueEvent(evt1.Clone());
      }
   }
   if (!destroy) {
      piece->moved = initialMoved;
   }
   return move;
}

std::string Board::moveHelper (std::string pos, Piece* piece) {
   if (checkmate()) {
      this->gameOver = -1 * (this->isWhitesTurn ? 1 : -1);
      std::cout << (!this->isWhitesTurn ? "White" : "Black") << " Won!" << '\n';
      return "";
   }
   if (stalemate ()) {
      this->gameOver = 0.1 * (this->isWhitesTurn ? 1 : -1);
      std::cout << (!this->isWhitesTurn ? "White" : "Black") << " Stalemated " << (!this->isWhitesTurn ? "Black" : "White") <<"!" << '\n';
      return "";
   }
   std::string output = "";
   bool startWhite = isWhitesTurn;
   if (!promotionMenuIsActive) {
      output = move (pos, piece);

      // means that the move was successful
      if (output != "") {
         
         // checks to see if it resulted in stalemate
         if (stalemate ()) {
            // checks to see if it was actually just checkmate then sets game score and outputs who won
            if (isInCheck()) {
               this->gameOver = -1 * (this->isWhitesTurn ? 1 : -1);
               std::cout << (!this->isWhitesTurn ? "White" : "Black") << " Won!" << '\n';
            } else {
               this->gameOver = 0.1 * (this->isWhitesTurn ? 1 : -1);
               std::cout << (!this->isWhitesTurn ? "White" : "Black") << " Stalemated " << (!this->isWhitesTurn ? "Black" : "White") <<"!" << '\n';
            }
         }
      }
   }

   return output;
}

std::string Board::move (std::string pos, Piece* piece){
   // clicked on a piece

   if (piece != nullptr) {
      // clicked a different piece on same team
      if (piece->isWhite == this->isWhitesTurn) {
         activePiece = piece;
      }
      // clicked a different piece on enemy team and its possible that it could be taken
      else if (activePiece != nullptr) {

         // test to make sure it's a legal move
         if (isValidMove (activePiece, pos)) {

            // enact the capture
            std::string output = confirmMove(activePiece, pos);

            if (output.length() != 0) {
               if ((output[0] == 'a') || 
                  (output[0] == 'b') ||
                  (output[0] == 'c') ||
                  (output[0] == 'd') ||
                  (output[0] == 'e') ||
                  (output[0] == 'f') ||
                  (output[0] == 'g') ||
                  (output[0] == 'h')) {
                  int* parsed = Square::parsePos(std::string(1, output[output.length() - 2]) + output[output.length() - 1]);
                  if (parsed[1] == 0) {
                     this->promotionMenuIsActive = true;
                     ((PromotionMenu*) this->promotionMenu)->show(true);
                  } else if (parsed[1] == 7) {
                     this->promotionMenuIsActive = true;
                     ((PromotionMenu*) this->promotionMenu)->show(false);
                  }
                  delete parsed;
               }
            }
            return output;
         }
      }
   }

   // clicked on a square and a piece was previously clicked 
   else if (activePiece != nullptr) {

      // test to make sure move is legal
      if (isValidMove (activePiece, pos)) {
         if (activePiece == nullptr) {
            return "";
         }
         // if its a pawn, check for enpassant
         if (activePiece->name == "pawn") {
            std::string initial = activePiece->position;
            if (pawnCapture (activePiece, pos)) {
               return std::string(1, initial[0]) + "x" + pos;
            }
         }
         if (activePiece->name == "king") {
            std::string initial = activePiece->position;
            if (checkKing (activePiece, pos, true)) {
               return this->prevMove;
            }
         }
         
         //if its not a pawn, do regular move
         std::string output = confirmMove(activePiece, pos);
         
         if (output.length() != 0) {
            if ((output[0] == 'a') || 
               (output[0] == 'b') ||
               (output[0] == 'c') ||
               (output[0] == 'd') ||
               (output[0] == 'e') ||
               (output[0] == 'f') ||
               (output[0] == 'g') ||
               (output[0] == 'h')) {
               int* parsed = Square::parsePos(std::string(1, output[output.length() - 2]) + output[output.length() - 1]);
               if (parsed[1] == 0) {
                  this->promotionMenuIsActive = true;
                  ((PromotionMenu*) this->promotionMenu)->show(true);
               } else if (parsed[1] == 7) {
                  this->promotionMenuIsActive = true;
                  ((PromotionMenu*) this->promotionMenu)->show(false);
               }
               delete parsed;
            }
         }
         return output;
      }
   }
   return "";
}


// checks to see if the move can be made, does not include taking pieces 
bool Board::isValidMove (Piece* piece, std::string pos, bool check) {
   if (piece == nullptr) {
      return false;
   }

   if (pos == piece->position) {
      return false;
   }

   int* first = Square::parsePos(piece->position);
   int* second = Square::parsePos(pos);
   bool val = false;

   if (pieceAtPosition (piece->position, piece->isWhite) && pieceAtPosition (piece->position, !piece->isWhite)) {
      delete[] first;
      delete[] second;
      return val;
   }

   if (pieceAtPosition (pos, piece->isWhite) && !pieceAtPosition (pos, !piece->isWhite)) {
      delete[] first;
      delete[] second;
      return val;
   }

   // test the piece and see if it can move
   if (piece->name == "pawn") {
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

   if (check && val && causesCheck(piece, pos)) {
      val = false; 
   }

   delete[] first;
   delete[] second;
   return val;
}

bool Board::checkPawnForward (Piece* piece, std::string pos) {

   // values

   int* first = Square::parsePos(piece->position);
   int* second = Square::parsePos(pos);
   int multiplier = 1;
   if (piece->isWhite) {
      multiplier = -1;
   }
   bool val = false;

   // move two spaces forward
   if (!piece->moved) { 
      if ((first[0] == second[0] && first[1] + 2 * multiplier == second[1]) && 
         !pieceAtPositionEither (first[0], first[1] + 1 * multiplier) && 
         !pieceAtPositionEither (first[0], first[1] + 2 * multiplier)) {
            val = true;
            canEnpassant = true;
         }
   }

   // move one space forward
   if (first[0] == second[0] && first[1] + 1 * multiplier == second[1] && 
            !pieceAtPositionEither (first[0], first[1] + 1 * multiplier)) {
      val = true;
   }
   // if (val) {
   //    if (second[1] == 0) {
   //       this->promotionMenuIsActive = true;
   //       ((PromotionMenu*) this->promotionMenu)->show(false);
   //    } else if (second[1] == 7) {
   //       this->promotionMenuIsActive = true;
   //       ((PromotionMenu*) this->promotionMenu)->show(true);
   //    }
   // }

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
      if (!pieceAtPositionEither (second[0], second[1])) {
         // check for en passant

         Piece* adjPiece = getPieceAt (second[0], second[1] - multiplier);
         if (adjPiece == nullptr) {
            val = false;
         }
         
         // enpassant
         else if (adjPiece->isWhite != piece->isWhite && adjPiece->name == "pawn" && this->canEnpassant) {
            if (pos[0] == adjPiece->position[0]) {

                // if piece is white 
               if (piece->isWhite) {
                  if (pos[1] == '6') {
                     if (this->prevMove[0] == pos[0] && std::strcmp(&this->prevMove[1], "5") == 0) {
                        if (enact) {
                           confirmMove(piece, pos);
                           if (GUI) {
                              wxThreadEvent evt( wxEVT_CHECKBOX, this->getSquare (adjPiece->position)->GetId());
                              wxTheApp->QueueEvent (evt.Clone());
                           }
                           pw->removePiece(adjPiece->position);
                           pb->removePiece(adjPiece->position);
                        }
                        val = true;
                     }
                  }
               }

               // if piece is black 
               else {
                  if (pos[1] == '3') {
                     if (this->prevMove[0] == pos[0] && std::strcmp(&this->prevMove[1], "4") == 0) {
                        if (enact) {
                           confirmMove(piece, pos);
                           if (GUI) {
                              wxThreadEvent evt( wxEVT_CHECKBOX, this->getSquare (adjPiece->position)->GetId());
                              wxTheApp->QueueEvent (evt.Clone());
                           }
                           pw->removePiece(adjPiece->position);
                           pb->removePiece(adjPiece->position);
                        }
                        val = true;
                     }
                  }
               }
            }
         }

         // enpassant failed 
         else {
            val = false;
         }
      } 
      
      // regular capture
      else {
         if (enact) { 
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

   // makes sure that it isnt in the same row or column
   if (first[0] == second[0] || first[1] == second[1]) {
      return false;
   }

   // makes sure it is three spaces away
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
      //checks diagonals like these
      //b5-f1
      //f1-b5
      for (int i = 1; i < std::abs(first[0] - second[0]); i++) {
         if (pieceAtPositionEither (second[0] + i * multiplier, second[1] - i * multiplier)) {
            return false;
         }
      }
      return true;
   } else if (second[0] - first[0] == second[1] - first[1]) { 
      //checks diagonals like these
      //h3-f1
      //f1-h3
      int multiplier = -1;
      if (second[1] > first[1]) {
         multiplier = 1;
      }
      for (int i = 1; i < std::abs(first[0] - second[0]); i++) {
         if (pieceAtPositionEither (second[0] - i * multiplier, second[1] - i * multiplier)) {
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
         if (pieceAtPositionEither (first[0], (i + 1) * multiplier + first[1])) {
            return false;
         }
      }
   } 
   // same row
   else {
      int multiplier = -1;
      if (second[0] > first[0]) {
         multiplier = 1;
      }
      for (int i = 0; i < std::abs(second[0] - first[0]) - 1; i++) {
         if (pieceAtPositionEither (first[0] + (i + 1) * multiplier, first[1])) {
            return false;
         }
      }
   }

   return true;
}

bool Board::checkKing (Piece* piece, std::string pos, bool enact) {
   int* first = Square::parsePos(piece->position);
   int* second = Square::parsePos(pos);
   bool val = false;

   // if its just right nearby its good to go
   if (std::abs(first[0] - second[0]) + std::abs(first[1] - second[1]) == 1) {
      if (enact) {
         confirmMove (piece, pos);
      }
      val = true;
   }
   
   // if its diagonal its good to go
   else if (std::abs(first[0] - second[0]) + std::abs(first[1] - second[1]) == 2) {
      if ((first[0] == second[0] || first[1] == second[1]) && piece->moved) {
         val = false;
      }
      else if (first[0] != second[0] && first[1] != second[1]) {
         if (enact) {
            confirmMove (piece, pos);
         }
         val = true;
      }

      // castle options
      else if (!piece->moved && !isInCheck()){
         // castle queen-side
         if (first[1] - second[1] > 0) {
            std::string rookPlacement = "d";
            rookPlacement.push_back((char) piece->position[1]);
            std::string check = "b";
            check.push_back((char) piece->position[1]);

            Piece* rook = this->isWhitesTurn ? this->pw->pieces[8] : this->pb->pieces[8];

            int* arr = Square::parsePos(check);
            if (rook != nullptr && !rook->moved) {
               if (checkStraight (first, arr)) {
                  if (!causesCheck (piece, rookPlacement) && !causesCheck (piece, pos)) {
                     if (enact) {
                        std::cout << "O-O-O ";
                        if (!isWhitesTurn) {
                           std::cout << '\n';
                        }
                        confirmMove (rook, rookPlacement);
                        confirmMove (piece, pos);
                        this->prevMove = "O-O-O";
                        activePiece = nullptr;
                        canEnpassant = false;
                        isWhitesTurn = !isWhitesTurn;
                     }
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

            Piece* rook = this->isWhitesTurn ? this->pw->pieces[9] : this->pb->pieces[9];

            int* arr = Square::parsePos(check);
            if (rook != nullptr && !rook->moved) {
               if (checkStraight (first, arr)) {
                  if (!causesCheck (piece, rookPlacement) && !causesCheck (piece, pos)) {
                     if (enact) {
                        std::cout << "O-O ";
                        if (!isWhitesTurn) {
                           std::cout << '\n';
                        }
                        confirmMove (piece, pos);
                        confirmMove (rook, rookPlacement);
                        this->prevMove = "O-O";
                        activePiece = nullptr;
                        canEnpassant = false;
                        isWhitesTurn = !isWhitesTurn;
                     }
                     val = true;
                  }
               }
            }
            delete[] arr;
         }
      }
   }
   
   delete[] first;
   delete[] second;
   return val;
}

// needs to pretend that the piece has moved to the location and search to see if king is now in check.

// move it, check to see if valid, move it back, return true/false
bool Board::causesCheck (Piece* piece, std::string pos) {

   // keeping valuees for returning confirmMove back to original state
   if (piece == nullptr) {
      return true;
   }

   std::string initialpos = piece->position;
   bool initialMoved = piece->moved;
   std::string prev = this->prevMove;
   bool isWhitesTurn = this->isWhitesTurn;

   confirmMove (piece, pos, false);

   Piece* checkingPiece = isInCheck ();

   confirmMove (piece, initialpos, false); 

   this->isWhitesTurn = isWhitesTurn;
   piece->moved = initialMoved;
   this->prevMove = prev;
   // return false ;
   return checkingPiece != nullptr;
} 

Piece* Board::isInCheck () {

   // sets current player
   Player* current = this->isWhitesTurn ? (Player*) this->pw : (Player*) this->pb;
   Player* next = this->isWhitesTurn ? (Player*) this->pb : (Player*) this->pw;
   
   Piece* currentKing = current->pieces[15];
   // std::cout << "testing" << (this->isWhitesTurn ? " white king\n" : " black king\n");
   // std::this_thread::sleep_for (std::chrono::microseconds(50000));
   for (int i = 0; i < 16; i++) {
      // makes sure piece isnt killed
      Piece* nextPiece = next->pieces[i];
      if (nextPiece != nullptr) {
         // std::cout << "testing" << nextPiece->name << " at " << nextPiece->position << '\n';
         // std::cout << (isValidMove (nextPiece, currentKing->position, false) ? "it is valid" : "it is not valid");
         if (isValidMove (nextPiece, currentKing->position, false)) {
            return nextPiece;
         }
      }
   }
   return nullptr;
}

// if is in stalemate but also currently in check
bool Board::checkmate () {
   if (this->isWhitesTurn) {
      if (isInCheck() == nullptr) {
         return false;
      }
   } else {
      if (isInCheck() == nullptr) {
         return false;
      }
   }

   return stalemate();
}


bool Board::stalemate () {
   if (!enoughPiecesToWin()) {
      return true;
   }
   bool isWhitesTurn = this->isWhitesTurn;
   // sets current player
   Player* current = this->isWhitesTurn ? (Player*) this->pw : (Player*) this->pb;

   Piece* currentKing = current->pieces[15];
   for (int i = 0; i < 16; i++) {

      // makes sure piece isnt killed
      Piece* currentPiece = current->pieces[i];
      if (currentPiece != nullptr) {
         getValidMoves(currentPiece);
         if (currentPiece->validMoveCount != 0) {
            return false;
         }
      } 
   }
   
   return true;
}

bool Board::enoughPiecesToWin () {
   Player* player = this->pw;
   for (int k = 0; k < 2; k++) {
      for (int i = 0; i < 8; i++) {
         if (player->pieces[i] != nullptr) {
            return true;
         }
      }
      if (player->pieces[8] != nullptr || 
         player->pieces[9] != nullptr || 
         player->pieces[14] != nullptr){
            return true;
         }
      
      if (((player->pieces[10] != nullptr || player->pieces[11] != nullptr) && 
         (player->pieces[12] != nullptr || player->pieces[13])) ||
         (player->pieces[12] != nullptr && player->pieces[13])) {
            return true;
         }
      player = pb;
   }
   return false;
}

std::string* Board::getValidMoves(Piece* piece) {
   if (piece == nullptr) {
      return nullptr;
   }
   piece->validMoveCount = 0;
   std::string* validMoves = new std::string[64];
   std::string initialPos = piece->position;
   for (int j = 0; j < 8; j++) {
      for (int k = 0; k < 8; k++) {
         // generate position
         std::string posToCheck = std::string (1, (char) ('a' + j));
         posToCheck.push_back((char) ('0' + k + 1));
         // make sure that the position isnt on itself because its kinda funky if it is
         if (std::strcmp (initialPos.c_str(), posToCheck.c_str()) != 0) {
            // try to move there (while making sure it doesnt cause check)
            if (isValidMove(piece, posToCheck)) {
               validMoves[piece->validMoveCount] = posToCheck;
               piece->validMoveCount++;
            }
         }
      }
   }
   return validMoves;
}

#endif