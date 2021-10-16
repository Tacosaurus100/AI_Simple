#ifndef BASIC_LAYER_HPP
#define BASIC_LAYER_HPP

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/classes/Basic3DWeightList.hpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;

namespace artificialIntelligence {
   namespace classes {

      template <typename T>
      class BasicLayer{
         private:
            Matrix3D<T>* layerMatrix;
            Matrix3D<T>* biasMatrix;
            Basic3DWeightList<T>* weights;
            BasicLayer* next;

         public:
            BasicLayer (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);

            BasicLayer (int length, int width, int height);

            BasicLayer ();

            int print (int depth, bool printWeights = false, bool printBias = false);

            BasicLayer<T>* add (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);

            Matrix3D<T>* getLayerMatrix ();

            Matrix3D<T>* setWeights (BasicWeight<T> weights);
      };
   }
}
#endif