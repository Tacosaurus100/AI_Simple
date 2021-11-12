#ifndef TEST_GENERATIONAL_AI_BASIC
#define TEST_GENERATIONAL_AI_BASIC

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
#include <cmath>

using namespace coreutils::classes::matrixes;
using namespace coreutils::functions;
using namespace artificialIntelligence::functions::activation;
using namespace artificialIntelligence::functions::layer;
using namespace artificialIntelligence::functions::backPropagation;
using namespace artificialIntelligence::classes;
using namespace std;

namespace artificialIntelligence {
   namespace basicLearningTypes {
      namespace testGenerationalAIBasic {
         static void run (int epochs, double learningRate, Matrix3D<float>** inputDataMatrixes, Matrix3D<float>** outputDataMatrixes, int inputCount, int hiddenLayerCount) {

            // making hidden layers with only 2 nodes
            const int hiddenLayerLength = 3;
            const int hiddenLayerWidth = 3;
            const int hiddenLayerHeight = 3;

            learningRate = learningRate;

            BasicLayerList<float>* list = new artificialIntelligence::classes::BasicLayerList<float> ();
            
            // input layer
            list->add (inputDataMatrixes[0]);

            list->editRootMatrix(inputDataMatrixes[0]);

            // hidden layers
            for (int i = 0; i < hiddenLayerCount; i++) {
               list->addNew (hiddenLayerLength, hiddenLayerWidth, hiddenLayerHeight);
            }

            // this is the output layer
            list->addNew (outputDataMatrixes[0]->getLength(), outputDataMatrixes[0]->getWidth(), outputDataMatrixes[0]->getHeight());

            int* order = new int[inputCount];
            for (int i = 0; i < inputCount; i++) {
               order[i] = i;
            }

            // main loop

            std::cout << std::fixed;
            std::cout << std::setprecision(2);
            for (int e = 0; e < epochs; e++) {
               // because stochastic gradient descent, the order needs randomization
               
               std::cout << "\n" << e / (double) epochs * 100 << "%";

               sort::shuffle(order, inputCount);

               // debug::printArr(order, inputCount);
               // for (int i = 0; i < inputCount; i++) {
               //    cout << "Input Matrixes " << i << ":";
               //    inputDataMatrixes[order[i]]->printMatrix();
               //    cout << "Output Matrix " << i << ":";
               //    outputDataMatrixes[order[i]]->printMatrix();
               // }
               // exit (0);
               for (int i = 0; i < inputCount; i++) {
                  // set the input layer for the backpropagation

                  // possibly has memory leaks

                  list->editRootMatrix(inputDataMatrixes[order[i]]);
 
                  // has memory leaks
                  list->calculateAndUpdateAll();

                  BasicLayer<float>* currentLayer = list->getLast();
                  // list->getRoot()->getLayerMatrix()->printMatrix();
                  // std::cout << "\n\n\n\n";
                  Matrix3D<float>* currentLayerMatrix = currentLayer->getLayerMatrix();
                  Matrix3D<float>* error = *(outputDataMatrixes[order[i]]) - currentLayerMatrix;
                  Matrix3D<float>* dSig = dSigmoid (currentLayerMatrix);
                  Matrix3D<float>* deltaNext = *error * (dSig);
                  Matrix3D<float>* deltaPrev = new Matrix3D<float> (deltaNext->getLength(), deltaNext->getWidth(), deltaNext->getHeight());
                  // error->printMatrix();
                  // deltaPrev->printMatrix();
                  delete dSig;
                  delete error;

                  deltaPrev->setMatrix(deltaNext);

                  // list->getLast()->print(true);

                  // updates the bias for the final layer
                  Matrix3D<float>* bias = *deltaNext * learningRate;
                  currentLayer->setBiasMatrix(bias);
                  delete bias;


                  // currentLayer->getLayerMatrix()->printMatrix();
                  
                  // now currentLayer is a hidden layer
                  currentLayer = currentLayer->getPrev();
                  
                  // may cause memory leak
                  while (currentLayer->getPrev() != nullptr) {
                     // get the matrix for this layer
                     
                     currentLayerMatrix = currentLayer->getLayerMatrix();

                     delete deltaPrev;
                     deltaPrev = new Matrix3D<float> (deltaNext->getLength(), deltaNext->getWidth(), deltaNext->getHeight());
                     deltaPrev->setMatrix(deltaNext);

                     // then calculate delta for the hidden layers
                     // run through each node, and get the error for each node 
                     

                     // <--> //


                     // gets the current node
                     error = new Matrix3D<float> (currentLayerMatrix->getLength(), currentLayerMatrix->getWidth(), currentLayerMatrix->getHeight());
                     for (int l = 0; l < currentLayerMatrix->getLength(); l++) {
                        for (int w = 0; w < currentLayerMatrix->getWidth(); w++) {
                           for (int h = 0; h < currentLayerMatrix->getHeight(); h++) {
                              // currentLayer->getWeights(i, j, k) gets the current node weight matrix
                              // deltaPrev->getData(i, j, k) gets the 

                              // the weighted matrix
                              Matrix3D<float>* weightedMatrix = *currentLayer->getWeights(l, w, h) * deltaPrev;
                              
                              // the error for this node is weightedMatrix->sum()
                              error->insert(weightedMatrix->sum(), l, w, h);
                              delete weightedMatrix;
                           }
                        }
                     }
                     
                     // std::cout << "start" << "\n";
                     // error->printMatrix();
                     // the delta of the next one equals the error times dSigmoid at each node

                     delete deltaNext;
                     Matrix3D<float>* dSig = dSigmoid (currentLayerMatrix);
                     deltaNext = *error * dSig;
                     
                     // deltaNext->printMatrix();
                     // std::cout << "end" << "\n";
                     // setting the bias matrix
                     Matrix3D<float>* bias = *deltaNext * learningRate;
                     currentLayer->setBiasMatrix(bias);
                     delete bias;


                     // <--> //
                     
                     // set output weights
                     for (int l = 0; l < currentLayerMatrix->getLength(); l++) {
                        for (int w = 0; w < currentLayerMatrix->getWidth(); w++) {
                           for (int h = 0; h < currentLayerMatrix->getHeight(); h++) {
                              // up to here gets each node in the matrix
                              float* nodeValue = currentLayerMatrix->getData(l, w, h);

                              Matrix3D<float>* weightMatrix = currentLayer->getWeights(l, w, h);

                              float value = 0;
                              // std::cout << l << " " << w << " " << h << "\n";
                              for (int l2 = 0; l2 < weightMatrix->getLength(); l2++) {
                                 for (int w2 = 0; w2 < weightMatrix->getWidth(); w2++) {
                                    for (int h2 = 0; h2 < weightMatrix->getHeight(); h2++) {
                                       // up to here gets each weight in each node
                                       // weight = 
                                       // std::cout << l2 << " " << w2 << " " << h2 << "\n"
                                       value = *weightMatrix->getData(l2, w2, h2) + *nodeValue * *deltaPrev->getData(l2, w2, h2) * learningRate;
                                       weightMatrix->insert(value, l2, w2, h2);
                                    }
                                 }
                              }
                           }
                        }
                     }

                     delete dSig;
                     delete error;
                     
                     // set the current layer to the previous layer
                     currentLayer = currentLayer->getPrev();
                  }

                  delete deltaNext;
                  delete deltaPrev;

                  
                  // list->getLast()->print(true, true);
               }
               // list->getLast()->print();
               if (isnan (*list->getLast()->getLayerMatrix()->getData(0,0,0))) {
                  std::cout << "here2";
                  exit (0);
               }
            }

            list->print(true, true);

            // output results
            for (int i = 0; i < inputCount; i++) {
               std::cout << "Input Matrix: ";
               inputDataMatrixes[i]->printMatrix();
               std::cout << "True Output: ";
               outputDataMatrixes[i]->printMatrix();
               std::cout << "Calculated Output: ";
               list->editRootMatrix(inputDataMatrixes[i]);
               list->calculateAndUpdateAll();
               list->getLast()->getLayerMatrix()->printMatrix();
            }
            std::cout << "\n\n\n\n";
            list->editRootMatrix(inputDataMatrixes[0]);
            list->calculateAndUpdateAll();
            list->getLast()->getLayerMatrix()->printMatrix();

            list->editRootMatrix(inputDataMatrixes[1]);
            list->calculateAndUpdateAll();
            list->getLast()->getLayerMatrix()->printMatrix();

            list->editRootMatrix(inputDataMatrixes[2]);
            list->calculateAndUpdateAll();
            list->getLast()->getLayerMatrix()->printMatrix();
            
            std::cout << std::setprecision(4);
            double sum = 0;
            for (int i = 0; i < inputCount; i++) {
               list->editRootMatrix(inputDataMatrixes[i]);
               list->calculateAndUpdateAll();
               
               // (*outputDataMatrixes[i] -list->getLast()->getLayerMatrix())->printMatrix();
               // exit (0);
               std::cout << *outputDataMatrixes[i]->getData(0, 0, 0) << " :: " << *list->getLast()->getLayerMatrix()->getData(0, 0, 0) << " :: " << (*outputDataMatrixes[i] - list->getLast()->getLayerMatrix())->sum() * 100;
               sum += (*outputDataMatrixes[i] - list->getLast()->getLayerMatrix())->sum() * 100 > 0 ? (*outputDataMatrixes[i] - list->getLast()->getLayerMatrix())->sum() * 100 : (*outputDataMatrixes[i] - list->getLast()->getLayerMatrix())->sum() * 100 * -1;
               std::cout << "%" << " error\n";
               // list->getLast()->getLayerMatrix()->printMatrix();
            }
            std::cout << "Total error :: " << sum << "%";


            delete[] order;
         }
      }
   }
}

#endif