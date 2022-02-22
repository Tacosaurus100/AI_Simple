#ifndef TRAIN_CHESS_AI_HPP
#define TRAIN_CHESS_AI_HPP

#include <artificialIntelligence/classes/BasicLayerList.hpp>

#include <chess/Board.hpp>
#include <chess/artificialIntelligence/ChessAI.hpp>

namespace chess {
   namespace artificialIntelligence {
      namespace train {
         BasicLayerList<float>* trainNetwork (ChessAI* ai, double score);

         static void consolidateAI (BasicLayerList<float>* layer, ChessAI* ai);

         static BasicLayerList<float>* generateModel (int buildType = 0);
      }
   }
}

#endif