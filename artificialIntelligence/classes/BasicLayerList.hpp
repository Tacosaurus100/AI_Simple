#ifndef BASIC_LAYER_LIST_HPP
#define BASIC_LAYER_LIST_HPP

#include <iostream>

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/classes/BasicLayer.hpp>
#include <artificialIntelligence/classes/Basic3DWeightList.hpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;

namespace artificialIntelligence {
   namespace classes {

      template <typename T>
      class BasicLayerList {
         public:
            BasicLayerList (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);
            
            BasicLayerList ();

            void printList (bool printWeights = false);

            void add (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);

            void addNew (int length, int width, int height);

         private:
            BasicLayer<T>* root;

      };
   }
}


#endif