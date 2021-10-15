#ifndef BASIC_3D_LAYER_LIST
#define BASIC_3D_LAYER_LIST

#include <artificialIntelligence/classes/Basic3DLayerList.hpp>

using namespace artificialIntelligence::classes;

template <typename T>
Basic3DLayerList<T>::Basic3DLayerList (int length, int width, int height) {
   this->root = new BasicLayerList<BasicLayerList<BasicLayerList<Matrix3D<T>>>>();
}

template <typename T>
Matrix3D<T>* Basic3DLayerList<T>::getWeightMatrix (int length, int width, int height) {
   return new Matrix3D<T> (1, 1, 1);
}

template <typename T>
void Basic3DLayerList<T>::insert (int length, int width, int height, Matrix3D<T> weightMatrix) {
   return;
}

#endif