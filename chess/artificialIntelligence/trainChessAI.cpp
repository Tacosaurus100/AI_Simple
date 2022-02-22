#ifndef TRAIN_CHESS_AI_CPP
#define TRAIN_CHESS_AI_CPP

#include <artificialIntelligence/classes/BasicLayerList.cpp>
#include <artificialIntelligence/basicLearningTypes/generationalAIBasic.cpp>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <chess/artificialIntelligence/trainChessAI.hpp>
#include <chess/Square.hpp>

BasicLayerList<float>* chess::artificialIntelligence::train::trainNetwork (ChessAI* ai, double score) {
   double learningRate = .1;

   BasicLayerList<float>* model = ai->model;
   if (model == nullptr) {
      return chess::artificialIntelligence::train::generateModel();
   }
   int multiplier = 1;
   if (score < 0) {
      multiplier = -1;
   }
   int winMultiplier = 100;
   Matrix3D<float>** outputMatrixes = new Matrix3D<float>* [ai->counter];
   for (int i = 0; i < ai->counter; i++) {
      outputMatrixes[i] = new Matrix3D<float> (1, 1, 1);
      // int* pos = Square::parsePos (ai->outputMoves[i]);
      // outputMatrixes[i]->insert (score * winMultiplier + ai->inputStates[i]->sum() / 100.0 * multiplier, 0, 0, pos[0] * 8 + pos[1]);
      // delete pos;a

      outputMatrixes[i]->insert (sigmoid(score * winMultiplier + ai->inputStates[i]->sum() / 100.0 * multiplier), 0, 0, 0);
   }
   // std::cout << *outputMatrixes[0]->getData(0, 0, 0) << '\n';
   // std::cout << *outputMatrixes[10]->getData(0, 0, 0) << '\n';
   // std::cout << ai->inputStates[ai->counter - 2]->sum() / 100.0<< '\n';
   std::cout << "running epoch\n";
   if (ai->counter >= 1) {
      ::artificialIntelligence::basicLearningTypes::generationalAIBasic::run(ai->model, 1, learningRate, ai->inputStates, outputMatrixes, ai->counter);
   }
   std::cout << "ending epoch\n";
   return model;
   //model, int epochs, double learningRate, Matrix3D<float>** inputDataMatrixes, Matrix3D<float>** outputDataMatrixes, int inputCount, bool print = false
}

BasicLayerList<float>* chess::artificialIntelligence::train::generateModel (int buildType) {
   BasicLayerList<float>* model = new BasicLayerList<float>();
   model->addNew(1, 8, 8);
   switch (buildType) {
      case 1:
         model->addNew(5, 5, 5);
         model->addNew(4, 4, 4);
         model->addNew(3, 3, 3);
         break;
      case 2:
         model->addNew(5, 5, 5);
         model->addNew(5, 5, 5);
         model->addNew(5, 5, 5);
         model->addNew(5, 5, 5);
         model->addNew(3, 3, 3);
         break;
      case 3:
         model->addNew(5, 5, 5);
         model->addNew(3, 3, 3);
         break;
      case 4:
         model->addNew(3, 3, 3);
         model->addNew(3, 3, 3);
         model->addNew(3, 3, 3);
         model->addNew(3, 3, 3);
         model->addNew(3, 3, 3);
         break;
      case 5:
         model->addNew(4, 4, 4);
         model->addNew(4, 4, 4);
         model->addNew(4, 4, 4);
         model->addNew(4, 4, 4);
         model->addNew(4, 4, 4);
         break;
      case 6:
         model->addNew(3, 3, 3);
         model->addNew(4, 4, 4);
         model->addNew(5, 5, 5);
         break;
      case 8:
         model->addNew(4, 4, 4);
         model->addNew(3, 3, 3);
         model->addNew(3, 3, 3);
         model->addNew(3, 3, 3);
         model->addNew(4, 4, 4);
         break;
      default:
         model->addNew(2, 2, 2);
         break;
   }
   model->addNew(1, 1, 1);
   return model;
}
   

#endif