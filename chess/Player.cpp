#ifndef CHESS_PLAYER_CPP
#define CHESS_PLAYER_CPP

#include <string>

#include <chess/Player.hpp>

void Player::removePiece (std::string pos) {
   for (int i = 0; i < 16; i++) {
      if (this->pieces[i] != nullptr) {
         if (this->pieces[i]->position == pos) {
            this->pieces[i] = nullptr;
            return;
         }
      }
   }
}

#endif