#ifndef BASIC_LAYER_LIST
#define BASIC_LAYER_LIST

#include <iostream>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <artificialIntelligence/classes/BasicLayerList.hpp>
#include <artificialIntelligence/classes/BasicLayer.cpp>
#include <artificialIntelligence/classes/Basic3DWeightList.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::functions::layer;
using namespace artificialIntelligence::classes;

template <typename T>
BasicLayerList<T>::BasicLayerList (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix, Basic3DWeightList<T>* weights){
   this->root = new BasicLayer<T> (layer, biasMatrix, weights);
}

template <typename T>
BasicLayerList<T>::BasicLayerList () {
   this->root = nullptr;
}

template <typename T>
void BasicLayerList<T>::printList (bool printWeights) {
   int depth = this->root->print(1, printWeights);
   std::cout << "There are " << depth << " total layers\n";
}

template <typename T>
void BasicLayerList<T>::add (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, Basic3DWeightList<T>* weights) {
   if (this->root == nullptr) {
      this->root = new BasicLayer<T> (layerMatrix, biasMatrix, weights);
   } else {
      this->root = this->root->add(layerMatrix, biasMatrix, weights);
   }
}

template <typename T>
void BasicLayerList<T>::addNew (int length, int width, int height) {
   Matrix3D<T>* layerMatrix = new Matrix3D<T> (length, width, height);
   Matrix3D<T>* biasMatrix = new Matrix3D<T> (length, width, height);
   layerMatrix->randomize();
   biasMatrix->randomize();
   if (this->root == nullptr) {
      this->root = new BasicLayer<T> (layerMatrix, biasMatrix);
   } else {
      this->root->add(layerMatrix, biasMatrix);
   }
}


#endif