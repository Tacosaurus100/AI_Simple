#ifndef LAYER_FUNCTIONS_HPP
#define LAYER_FUNCTIONS_HPP

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/classes/BasicLayerList.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::functions::activation;
using namespace artificialIntelligence::classes;

namespace artificialIntelligence {
   namespace functions {
      namespace layer {
         // moves a layer forward to the next layer if theyre the same width and height
         template <typename T>
         void layerToLayerForward (Matrix3D<T>* firstLayer, Matrix3D<T>* secondLayer, BasicLayerList<Matrix3D<T>>* secondLayerWeights, Matrix3D<T>* secondLayerBias);

         template <typename T>
         Matrix3D<T>* newLayer (int length, int width, int height);

         template <typename T>
         BasicLayerList<Matrix3D<T>>* newWeight (BasicLayerList<T>* firstLayer, BasicLayerList<Matrix3D<T>>* secondLayer);
      }
   }
}

#endif