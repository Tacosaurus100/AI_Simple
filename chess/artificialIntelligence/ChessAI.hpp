#ifndef CHESS_AI_HPP
#define CHESS_AI_HPP


#define MAX_MOVES 30

// #include <artificialIntelligence/classes/BasicLayerList.hpp>

#include <chess/Board.hpp>
#include <chess/Piece.hpp>
#include <chess/Square.hpp>

#include <artificialIntelligence/classes/BasicLayerList.hpp>

#include <coreutils/classes/matrixes/Matrix3D.cpp>


using namespace coreutils::classes::matrixes;

namespace chess {
   class ChessAI{
      public:
         ChessAI (bool isWhite, BasicLayerList<float>* list = nullptr);

         static Matrix3D<float>* generateInput (Board* board, int isWhite);

         // wxThreadError Run ();

         Matrix3D<float>** inputs;
         Matrix3D<float>** outputs;

         void makeRandomMove (Board* board);
         void makeDeterminedMove (Board* board);
         void makeMove (Board* board, Square* square, Piece* piece);

         bool isWhite;
         Matrix3D<float>** inputStates;
         std::string* outputMoves;
         int* pieceMoved;
         int counter;
         BasicLayerList<float>* model;
   };
}

#endif 