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
            BasicLayer* prev;

         public:
            BasicLayer (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);

            BasicLayer (int length, int width, int height);

            BasicLayer ();

            int print (bool printBias = false, bool printWeights = false, int depth = 1);

            BasicLayer<T>* add (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);

            void calculateAndUpdateAll ();

            void calculateAndUpdateSingle ();

            void setPrev (BasicLayer<T>* prev);

            Matrix3D<T>* getLayerMatrix ();

            void setLayerMatrix (Matrix3D<T>* layerMatrix);

            Matrix3D<T>* getWeights (int length, int width, int height);

            // void setWeights (BasicWeight<T> weights);

            Matrix3D<T>* getBias ();

            void setBiasMatrix (Matrix3D<T>* bias);

            BasicLayer<T>* getLast ();

            BasicLayer<T>* getNext ();

            BasicLayer<T>* getPrev ();
      };
   }
}
#endif