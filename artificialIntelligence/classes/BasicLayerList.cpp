#ifndef BASIC_LAYER_LIST
#define BASIC_LAYER_LIST

#include <iostream>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <artificialIntelligence/classes/BasicLayerList.hpp>
#include <artificialIntelligence/functions/layerFunctions.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::functions::layer;
using namespace artificialIntelligence::classes;

template <typename T>
BasicLayerList<T>::BasicLayerList (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights){
   this->root = new BasicLayer (layer, weights);
}

template <typename T>
BasicLayerList<T>::BasicLayerList () {
   this->root = nullptr;
}

template <typename T>
void BasicLayerList<T>::printList () {
   int depth = this->root->print(1, false);
   std::cout << "There are " << depth << " total layers\n";
}

template <typename T>
void BasicLayerList<T>::add (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights) {
   if (this->root == nullptr) {
      this->root = new BasicLayer (layer, weights);
   } else {
      this->root = this->root->add(layer, weights);
   }
}

template <typename T>
void BasicLayerList<T>::addNew (int length, int width, int height) {
   Matrix3D<T>* layer = new Matrix3D<T> (length, width, height);
   layer->randomize ();
   if (this->root == nullptr) {
      this->root = new BasicLayer (layer, nullptr);
   } else {
      this->root->add(layer);
   }
}

template <typename T>
BasicLayerList<T>::BasicLayer::BasicLayer (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights) {
   this->layer = layer;
   this->weights = weights;
   this->next = nullptr;
}

template <typename T>
BasicLayerList<T>::BasicLayer::BasicLayer () {
   this->layer = nullptr;
   this->weights = nullptr;
   this->next = nullptr;
}

template <typename T>
int BasicLayerList<T>::BasicLayer::print (int depth, bool printWeights) {
   std::cout << "Current Depth: " << depth << '\n';
   std::cout << "Layer Matrix: \n";
   this->layer->printMatrix();
   // if (printWeights) {
   //    for (int i = 0; i < this->weights->getLength(); i++){
   //       for (int k = 0; k < this->weights->getLength(); k++){
   //          for (int j = 0; j < this->weights->getLength(); j++){
   //             std::cout << "Weights [" << i << "][" << j << "][" << k << "]\n";
   //             this->weights->getData(i, j, k).printMatrix();
   //          }
   //       }
   //    }
   // }
   if (this->next == nullptr) {
      return depth;
   }
   depth = this->next->print(++depth, printWeights);
   return depth;
}  

//if it hits the end, it adds a new one to the back of the list and then
//returns the newly added node, along with a way to tell the previous node the weights needed
template <typename T>
void BasicLayerList<T>::BasicLayer::add (Matrix3D<T>* layer, BasicLayerList<Matrix3D<T>>* weights) {
   if (next == nullptr) {
      this->next = new BasicLayer (layer, weights);
      this->weights = newWeight(this, this->next);
      return;
   }
   this->next->add(layer, weights);
   return;
}

template <typename T>
Matrix3D<T>* BasicLayerList<T>::BasicLayer::getLayer () {
   return this->layer;
}

#endif