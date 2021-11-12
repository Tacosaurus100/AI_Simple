#ifndef LAYER_FUNCTIONS
#define LAYER_FUNCTIONS

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/layerFunctions.hpp>
#include <artificialIntelligence/classes/BasicLayerList.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>


using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::functions::activation;
using namespace artificialIntelligence::classes;

namespace artificialIntelligence {
   namespace functions {
      namespace layer {
         template <typename T>
         void layerToLayerForward (
                              Matrix3D<T>* firstLayer, 
                              Matrix3D<T>* secondLayer,
                              BasicLayerList<T>* secondLayerWeights,
                              Matrix3D<T>* secondLayerBias) 
         {
            // go through the second layer
            double activation = 0;
            for (int sl = 0; sl < secondLayer->getLength(); sl++) {

               // go through the width of the second Layer for 2d matrixes
               for (int sw = 0; sw < secondLayer->getWidth(); sw++) {
                  
                  // go through the height of the second layer for 3d matrixes
                  for (int sh = 0; sh < secondLayer->getHeight(); sh++) {

                     //secondLayer->getData(sl, sw, sh) is the node to be changed

                     // new value for the current node
                     activation = secondLayerBias->getData(sl, sw, sh);
                     // secondLayerWeights->getData(0, 0, 0).printMatrix();
                     // secondLayerWeights->getData(0, 1, 0).printMatrix();
                     // exit(0);
                     // modify everything in each node of the second layer
                     for (int fl = 0; fl < firstLayer->getLength(); fl++) {
                        for (int fw = 0; fw < firstLayer->getWidth(); fw++) {
                           for (int fh = 0; fh < firstLayer->getHeight(); fh++) {
                              // std::cout << "length" << firstLayer->getLength() << " width" << firstLayer->getWidth() << " height" << firstLayer->getHeight();
                              //secondLayerWeights->getData(fl, fw, fh) gets the matrix for that node of the weights
                              //secondLayerWeights->getData(fl, fw, fh)->getData(sl, sw, sh); gets the data at a specifc spot
                              // secondLayerWeights->getData(fl, fw, fh).printMatrix();
                              activation += firstLayer->getData(fl, fw, fh) * secondLayerWeights->getData(fl, fw, fh).getData(sl, sw, sh);
                           }
                        }
                     }

                     // put the data that was just found into the matrix
                     secondLayer->insert(sigmoid(activation), sl, sw, sh);
                  }
               }
            }
         }

         template <typename T>
         Matrix3D<T>* newLayer (int length, int width, int height) {
            return new Matrix3D<float> (length, width, height);
         }

         template <typename T>
         BasicWeight<T>* newWeight (BasicLayer<T>* firstLayer, BasicLayer<T>* secondLayer) {
            return new BasicWeight<T> (
               firstLayer->getLayerMatrix()->getLength(), 
               firstLayer->getLayerMatrix()->getWidth(),
               firstLayer->getLayerMatrix()->getHeight(),
               secondLayer->getLayerMatrix()->getLength(),
               secondLayer->getLayerMatrix()->getWidth(),
               secondLayer->getLayerMatrix()->getHeight());
         }
      }
   }
}

#endif