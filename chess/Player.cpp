#ifndef CHESS_PLAYER_CPP
#define CHESS_PLAYER_CPP

#include <string>

#include <chess/Player.hpp>

bool Player::removePiece (std::string pos) {
   for (int i = 0; i < 16; i++) {
      if (this->pieces[i] != nullptr) {
         if (this->pieces[i]->position == pos) {
            this->pieces[i] = nullptr;
            return true;
         }
      }
   }
   return false;
}

std::string Player::piecesThatExist () {
   std::string output = "";
   for (int i = 0; i < 16; i++) {
      if (this->pieces[i] != nullptr) {
         switch (this->pieces[i]->name.at(0)) {
            case 'p':
               output += "P";
               break;
            case 'b':
               output += "B";
               break;
            case 'r':
               output += "R";
               break;
            case 'q':
               output += "Q";
               break;
            case 'k':
               if (this->pieces[i]->name.length() == 6) {
                  output += "N";
               } else {
                  output += "K";
               }
               break;
         }
      }
   }
   return output;
}

#endif