#ifndef BASIC_LAYER_LIST_HPP
#define BASIC_LAYER_LIST_HPP

#include <iostream>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

using namespace coreutils::classes::matrixes;

namespace artificialIntelligence {
   namespace classes {

      template <typename T>
      class BasicLayerList {
         public:
            BasicLayerList (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights = nullptr);
            
            BasicLayerList ();

            void printList ();

            void add (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights = nullptr);

            void addNew (int length, int width, int height);

            class BasicLayer{
               private:
                  Matrix3D<T>* layer;
                  BasicLayerList<Matrix3D<T>>* weights;
                  BasicLayer* next;

               public:
                  BasicLayer (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights);

                  BasicLayer ();

                  int print (int depth, bool printWeights);

                  void add (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights = nullptr);

                  Matrix3D<T>* getLayer ();
            };

         private:
            BasicLayer* root;

      };
   }
}


#endif