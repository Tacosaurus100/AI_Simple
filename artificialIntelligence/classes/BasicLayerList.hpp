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

            void printList (bool printBias = false, bool printWeights = false);

            void add (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, Basic3DWeightList<T>* weights = nullptr);

            void addNew (int length, int width, int height);

            void calculateAndUpdateAll ();

            void calculateAndUpdateLast ();

            void editRootMatrix (Matrix3D<T>* newMatrix);

            BasicLayer<T>* getRoot ();

            BasicLayer<T>* getLast ();

         private:
            BasicLayer<T>* root;
            BasicLayer<T>* last;

      };
   }
}


#endif