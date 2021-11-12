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
            BasicLayerList (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, BasicWeight<T>* weights = nullptr);
            
            BasicLayerList ();

            void print (bool printBias = false, bool printWeights = false);

            void add (BasicLayer<T>* layer);

            void add (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, BasicWeight<T>* weights = nullptr);

            void addNew (int length, int width, int height);

            void calculateAndUpdateAll ();

            void calculateAndUpdateLast ();

            void editRootMatrix (Matrix3D<T>* newMatrix);

            BasicLayer<T>* getRoot ();

            BasicLayer<T>* getLast ();

            void toFile (std::string filepath);

            static BasicLayerList<T>* loadFromFile (std::string filepath);

         private:
            BasicLayer<T>* root;
            BasicLayer<T>* last;

      };
   }
}


#endif