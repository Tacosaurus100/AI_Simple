#ifndef BASIC_3D_LAYER_LIST_HPP
#define BASIC_3D_LAYER_LIST_HPP

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/classes/BasicLayerList.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;

namespace artificialIntelligence {
   namespace classes {
      template <typename T>
      class Basic3DLayerList {
         public:
            Basic3DLayerList (int length, int width, int height);

            Matrix3D<T>* getWeightMatrix (int length, int width, int height);

            void insert (int length, int width, int height, Matrix3D<T> weightMatrix);
         private:
            BasicLayerList<BasicLayerList<BasicLayerList<Matrix3D<T>>>> root;
      };
   }
}

#endif