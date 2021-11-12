#ifndef BASIC_3D_WEIGHT_LIST
#define BASIC_3D_WEIGHT_LIST

#include <artificialIntelligence/classes/Basic3DWeightList.hpp>
#include <artificialIntelligence/classes/BasicWeight.cpp>
#include <artificialIntelligence/classes/BasicLayerList.hpp>


using namespace artificialIntelligence::classes;

// makes a Basic3DWeightList with new, random weights at each spot with matrix size of sl, sw, sh
template <typename T>
Basic3DWeightList<T>::Basic3DWeightList (int fl, int fw, int fh, int sl, int sw, int sh) {
   this->root = new BasicWeight<T>(fl, fw, fh, sl, sw, sh);
}

// makes an empty Basic3DWeightList
template <typename T>
Basic3DWeightList<T>::Basic3DWeightList () {
   this->root = nullptr;
}

template <typename T>
void Basic3DWeightList<T>::print() {
   this->root->print();
}

// gets the weights for the specific node
template <typename T>
Matrix3D<T>* Basic3DWeightList<T>::getWeightMatrix (int length, int width, int height) {
   return this->root->getWeightMatrix (length, width, height);
}

// puts weights in a specific spot. They can not be put in without a spot
template <typename T>
void Basic3DWeightList<T>::insert (int length, int width, int height, Matrix3D<T> weights) {
   this->root = this->root->add (length, width, height, weights);
}

#endif