#ifndef GENERATIONAL_AI_BASIC
#define GENERATIONAL_AI_BASIC

#include <coreutils/classes/matrixes/Matrix.cpp>
#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <coreutils/functions/sort/sortHelpers.cpp>
#include <coreutils/functions/debug/print.cpp>


#include <artificialIntelligence/functions/layerFunctions.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>
#include <artificialIntelligence/functions/backPropagationFunctions.cpp>

#include <artificialIntelligence/classes/BasicLayerList.cpp>
#include <artificialIntelligence/classes/Basic3DWeightList.cpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace coreutils::classes::matrixes;
using namespace coreutils::functions;
using namespace artificialIntelligence::functions::activation;
using namespace artificialIntelligence::functions::layer;
using namespace artificialIntelligence::functions::backPropagation;
using namespace artificialIntelligence::classes;
using namespace std;

namespace artificialIntelligence {
   namespace basicLearningTypes {
      namespace generationalAIBasic {
         static void run (int epochs, double learningRate, Matrix3D<float>* inputLayer, Matrix3D<float>* outputLayerData, int inputCount, int hiddenLayerCount) {

            // making hidden layers with only 2 nodes
            const int hiddenLayerLength = 1;
            const int hiddenLayerWidth = 2;
            const int hiddenLayerHeight = 1;

            BasicLayerList<float>* list = new artificialIntelligence::classes::BasicLayerList<float> ();

            list->add (inputLayer);
            for (int i = 0; i < hiddenLayerCount; i++) {
               list->addNew (hiddenLayerLength, hiddenLayerWidth, hiddenLayerHeight);
            }
            list->printList(true);

            exit (0);
            // row:     0  1  2  3  4
            // input:   0  1  2  3  4
            // weights: 00000 11111 22222 33333 44444
            // output:  1  2  3  4  5

            // // makes the output layer bias and weights
            // hiddenLayerBias[hiddenLayerCount - 1] = Matrix3D<float> (outputLayerData->getLength(), outputLayerData->getWidth(), outputLayerData->getHeight());
            // hiddenLayerBias[hiddenLayerCount - 1].randomize();

            // Matrix3D<float>* outputLayers = new Matrix3D<float> [inputCount];
            // for (int i = 0; i < inputCount; i++){
            //    outputLayers[i] = Matrix3D<float> (outputLayerData->getLength(), outputLayerData->getWidth(), outputLayerData->getHeight());
            //    outputLayers[i].randomize();
            // }

            // for (int i = 0; i < inputCount; i++) {
            //    cout << "Output #" << i << '\n';
            //    outputLayers[i].printMatrix();
            // }
            
            // // main loop

            // each run needs to test every input and output
            // starts by shuffling
            // then calculates delta for output
            // then calculates delta for hidden
            // then calculates delta for input
            // then backpropagates
            for (int e = 0; e < epochs; e++) {
            //    // because stochastic gradient descent, the order needs randomization
               int* order = inputLayer->shuffleGroups();
               outputLayerData->shuffleGroups (order);


               // change the first hidden layer
            //    //for (int i = 0; i < inputLayer->getLength(); i++) {
            //    for (int i = 0; i < inputCount; i++) {
            //       // hiddenLayers[0].printMatrix();
            //       layerToLayerForward(&inputLayer[i], &hiddenLayers[0], &hiddenLayerWeights[0], &hiddenLayerBias[0]);
            //       // hiddenLayers[0].printMatrix();
                  
            //       // change the rest of the hidden layers
            //       for (int k = 1; k < hiddenLayerCount - 1; k++) {
            //          layerToLayerForward(&hiddenLayers[i - 1], &hiddenLayers[i], &hiddenLayerWeights[i], &hiddenLayerBias[i]);
            //       }

            //       // exit(0);
            //       // layerToLayerForward(&hiddenLayers[hiddenLayerCount - 1], &outputLayer[i], &hiddenLayerWeights[hiddenLayerCount - 1], &hiddenLayerBias[hiddenLayerCount - 1]);
            //       layerToLayerForward(&hiddenLayers[hiddenLayerCount - 1], &outputLayers[i], &hiddenLayerWeights[hiddenLayerCount - 1], &hiddenLayerBias[hiddenLayerCount - 1]);
                  
            //       // Matrix3D<float>* deltaOutput = meanSquareErrorHiddenLayer(&outputLayers[i], &outputLayerData[i], hiddenLayerCount, learningRate);
            //       // meanSquareErrorOutputLayer(&hiddenLayers[hiddenLayerCount - 1], &outputLayerData[i], hiddenLayerCount, learningRate);
            //       Matrix3D<float>* deltaHiddenOutput = new Matrix3D<float> [hiddenLayerCount];


            //       for (int j = hiddenLayerCount - 1; j >= 1; j--) {
            //          //errors here
            //          deltaHiddenOutput[j] = *meanSquareErrorHiddenLayer(&outputLayers[j], &outputLayerData[j], hiddenLayerCount, learningRate);
            //          // deltaHiddenOutput[j].printMatrix();
            //          // exit(0);

            //          updateBias(&hiddenLayerBias[j], &deltaHiddenOutput[j], learningRate);

            //          // go through each node in the layer and change each of their weights, backwards
            //          for (int fl = 0; fl < hiddenLayerLength; fl++) {
            //             for (int fw = 0; fw < hiddenLayerWidth; fw++) {
            //                for (int fh = 0; fh < hiddenLayerHeight; fh++) {
            //                   // the previous layer affects the output weight of the next one
            //                   // the triple for loop is to get every hidden weight in the set
            //                   hiddenLayerWeights[j].getData(fl, fw, fh).printMatrix();
            //                   std::cout << "\ndelta\n";
            //                   deltaHiddenOutput[j].printMatrix();;
            //                   std::cout << "\nhere\n";
            //                   cout << deltaHiddenOutput[j].getData(fl, fw, fh);
            //                   std::cout << "\nhere\n";
            //                   updateWeights(hiddenLayers[j - 1].getData(fl, fw, fh), hiddenLayerWeights[j].getData(fl, fw, fh), deltaHiddenOutput[j].getData(fl, fw, fh), learningRate);
            //                   hiddenLayerWeights[j].getData(fl, fw, fh).printMatrix();
            //                   std::cout << "\nhere\n";
            //                   // exit (0);
            //                }
            //             }
            //          }
            //       }
            //    }
               
            //    // exit (0);
            //    // change the output layer
            }
         }
      }
   }
}

#endif