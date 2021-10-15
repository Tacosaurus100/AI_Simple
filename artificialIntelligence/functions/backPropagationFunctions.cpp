#ifndef BACK_PROPAGATION
#define BACK_PROPAGATION

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::functions::activation;

namespace artificialIntelligence {
   namespace functions {
      namespace backPropagation {

         template <typename T>
         void updateBias (Matrix3D<float>* bias, Matrix3D<float>* delta, double learningRate);


         template <typename T>
         Matrix3D<T>* meanSquareErrorOutputLayer (Matrix3D<T>* firstLayer, Matrix3D<T>* realOutputs, int hiddenLayerCount, int learningRate) {
            Matrix3D<T>* deltaLayer = new Matrix3D<T> (firstLayer->getLength(), firstLayer->getWidth(), firstLayer->getHeight());

            // for (int sl = 0; sl < realOutputs->getLength(); sl++) {

            //    // go through the width of the second Layer for 2d matrixes
            //    for (int sw = 0; sw < realOutputs->getWidth(); sw++) {
                  
            //       // go through the height of the second layer for 3d matrixes
            //       for (int sh = 0; sh < realOutputs->getHeight(); sh++) {
            for (int fl = 0; fl < firstLayer->getLength(); fl++) {
               for (int fw = 0; fw < firstLayer->getWidth(); fw++) {
                  for (int fh = 0; fh < firstLayer->getHeight(); fh++) {
                     double dError = realOutputs->getData(fl, fw, fh) - firstLayer->getData(fl, fw, fh);
                     deltaLayer->insert(dError * dSigmoid(firstLayer->getData(fl, fw, fh)), fl, fw, fh);
                     // * firstLayer->getData(fl, fw, fh) * learningRate;
                     // firstLayer->insert(newVal, fl, fw, fh);
                  }
               }
            }
            //       }
            //    }
            // }
            return deltaLayer;
         }

         template <typename T>
         Matrix3D<T>* meanSquareErrorHiddenLayer (Matrix3D<T>* firstLayer, Matrix3D<T>* realOutputs, int hiddenLayerCount, double learningRate) {
            Matrix3D<T>* deltaHiddenLayer = new Matrix3D<T> (firstLayer->getLength(), firstLayer->getWidth(), firstLayer->getHeight());

            for (int sl = 0; sl < firstLayer->getLength(); sl++) {

               // go through the width of the second Layer for 2d matrixes
               for (int sw = 0; sw < firstLayer->getWidth(); sw++) {
                  
                  // go through the height of the second layer for 3d matrixes
                  for (int sh = 0; sh < firstLayer->getHeight(); sh++) {
                     float dError = 0;
                     for (int fl = 0; fl < realOutputs->getLength(); fl++) {
                        for (int fw = 0; fw < realOutputs->getWidth(); fw++) {
                           for (int fh = 0; fh < realOutputs->getHeight(); fh++) {
                              dError += realOutputs->getData(fl, fw, fh) - firstLayer->getData(sl, sw, sh);
                              // * firstLayer->getData(fl, fw, fh) * learningRate;
                              // firstLayer->insert(newVal, fl, fw, fh);
                           }
                        }
                     }
                     deltaHiddenLayer->insert(dError * dSigmoid(firstLayer->getData(sl, sw, sh)), sl, sw, sh);
                  }
               }
            }
            return deltaHiddenLayer;
         }

         template <typename T>
         void updateBias (Matrix3D<T>* bias, Matrix3D<T>* delta, double learningRate) {
            for (int fl = 0; fl < bias->getLength(); fl++) {
               for (int fw = 0; fw < bias->getWidth(); fw++) {
                  for (int fh = 0; fh < bias->getHeight(); fh++) {
                     float newBias = delta->getData(fl, fw, fh) * learningRate + delta->getData(fl, fw, fh);
                     bias->insert(newBias, fl, fw, fh);
                  }
               }
            }
         }

         template <typename T>
         void updateWeights (float layer, Matrix3D<T> weights, T delta, double learningRate) {
            std::cout << weights.getLength() << weights.getWidth() << weights.getHeight() << '\n';
            // std::cout << weights.getData(0, 1, 0);
            // exit (0);
            for (int fl = 0; fl < weights.getLength(); fl++) {
               for (int fw = 0; fw < weights.getWidth(); fw++) {
                  for (int fh = 0; fh < weights.getHeight(); fh++) {
                     float newWeight = layer * delta * learningRate;
                     // exit (0);
                     weights.insert(newWeight + weights.getData(fl, fw, fh), fl, fw, fh);
                  }
               }
            }
            // exit(0);
         }
      }
   }
}

#endif