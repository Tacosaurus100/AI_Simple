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
BasicLayerList<T>::BasicLayerList (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix, BasicWeight<T>* weights){
   this->root = new BasicLayer<T> (layer, biasMatrix, weights);
   this->last = this->root;
}

template <typename T>
BasicLayerList<T>::BasicLayerList () {
   this->root = nullptr;
   this->last = nullptr;
}

template <typename T>
void BasicLayerList<T>::print (bool printBias, bool printWeights) {
   if (this->root != nullptr) {
      int depth = this->root->print(printBias, printWeights);
      std::cout << "There are " << depth << " total layers\n";
   } else {
      std::cout << "No root layer initialized!\n";
   }
}

template <typename T>
void BasicLayerList<T>::add (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, BasicWeight<T>* weights) {
   if (this->root == nullptr) {
      this->root = new BasicLayer<T> (layerMatrix, biasMatrix, weights);
   } else {
      this->root = this->root->add(layerMatrix, biasMatrix, weights);
   }
   this->last = this->root->getLast();
}

template <typename T>
void BasicLayerList<T>::editRootMatrix (Matrix3D<T>* newMatrix) {
   if (this->root != nullptr) {
      this->root->setLayerMatrix(newMatrix);
   }
}

template <typename T>
void BasicLayerList<T>::calculateAndUpdateAll () {
   if (this->root != nullptr) {
      this->root->calculateAndUpdateAll();
   } else {
      std::cout << "No root layer initialized!\n";
   }
}

template <typename T>
void BasicLayerList<T>::calculateAndUpdateLast () {
   if (this->last != nullptr) {
      this->last->getPrev()->calculateAndUpdateAll();
   } else {
      std::cout << "No last layer initialized!\n";
   }
}

template <typename T>
void BasicLayerList<T>::add (BasicLayer<T>* layer) {
   if (this->last != nullptr) {
      this->last = this->last->add(layer);
   } else {
      this->root = layer;
      this->last = this->root;
   }
}

template <typename T>
void BasicLayerList<T>::addNew (int length, int width, int height) {
   Matrix3D<T>* layerMatrix = new Matrix3D<T> (length, width, height);
   layerMatrix->randomize();

   // Matrix3D<T>* biasMatrix = new Matrix3D<T> (length, width, height);
   // biasMatrix->randomize();
   if (this->root == nullptr) {
      this->root = new BasicLayer<T> (layerMatrix);
   } else {
      this->root->add(layerMatrix);
   }
   this->last = this->root->getLast();
}

template <typename T>
BasicLayer<T>* BasicLayerList<T>::getRoot () {
   return this->root;
}

template <typename T>
BasicLayer<T>* BasicLayerList<T>::getLast () {
   return this->last;
}

template <typename T>
void BasicLayerList<T>::toFile (std::string filepath) {
   ofstream outputFile;
   outputFile.open (filepath);
   this->root->toFile (&outputFile);
   outputFile.close();
}

template <typename T>
BasicLayerList<T>* BasicLayerList<T>::loadFromFile (std::string filepath) {
   BasicLayerList<T>* list = new BasicLayerList<T>();
   ifstream inputFile;
   inputFile.open (filepath);
   list->root = BasicLayer<float>::loadFromFile(&inputFile);
   list->last = list->root->getLast();
   inputFile.close();
   return list;
}

#endif