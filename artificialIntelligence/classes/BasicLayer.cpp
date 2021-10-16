#ifndef BASIC_LAYER
#define BASIC_LAYER

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/layerFunctions.cpp>
#include <artificialIntelligence/classes/BasicLayer.hpp>
#include <artificialIntelligence/classes/Basic3DWeightList.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;
using namespace artificialIntelligence::functions::layer;


// a weight list of lists of lists of Matrix3D<T>

template <typename T>
BasicLayer<T>::BasicLayer (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, Basic3DWeightList <T>* weights) {
   this->layerMatrix = layerMatrix;
   this->biasMatrix = biasMatrix;
   this->weights = weights;
   this->next = nullptr;
}

template <typename T>
BasicLayer<T>::BasicLayer (int length, int width, int height) {
   this->layerMatrix = new Matrix3D<T> (length, width, height);
   this->layerMatrix->randomize();

   this->biasMatrix = new Matrix3D<T> (length, width, height);
   this->biasMatrix->randomize();

   this->weights = nullptr;
   this->next = nullptr;
}

template <typename T>
BasicLayer<T>::BasicLayer () {
   this->layerMatrix = nullptr;
   this->biasMatrix = nullptr;
   this->weights = nullptr;
   this->next = nullptr;
}

template <typename T>
int BasicLayer<T>::print (int depth, bool printWeights, bool printBias) {
   std::cout << "\n\nCurrent Index: " << depth << '\n';
   std::cout << "Layer Matrix: \n";
   this->layerMatrix->printMatrix();
   std::cout << "Bias Matrix: \n";
   this->biasMatrix->printMatrix();
   if (printWeights) {
      if (this->weights != nullptr) {
         this->weights->print();
      } else {
         std::cout << "No weights found!\n";
      }
   }
   if (this->next == nullptr) {
      return depth;
   }
   depth = this->next->print(depth + 1, printWeights);
   return depth;
}  

//if it hits the end, it adds a new one to the back of the list and then
//returns the newly added node, along with a way to tell the previous node the weights needed
template <typename T>
BasicLayer<T>* BasicLayer<T>::add (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, Basic3DWeightList<T>* weights) {

   if (next == nullptr) {
      this->next = new BasicLayer (layerMatrix, biasMatrix, weights);
      this->biasMatrix = biasMatrix;
      this->weights = newWeight(this, this->next);
      return this;
   }
   this->next->add(layerMatrix, biasMatrix, weights);
   return this;
}

template <typename T>
Matrix3D<T>* BasicLayer<T>::getLayerMatrix () {
   return this->layerMatrix;
}

template <typename T>
Matrix3D<T>* BasicLayer<T>::setWeights (BasicWeight<T> weights) {
   this->weights = weights;
}

#endif