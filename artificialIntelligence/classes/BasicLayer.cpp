#ifndef BASIC_LAYER
#define BASIC_LAYER

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/layerFunctions.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>
#include <artificialIntelligence/classes/BasicLayer.hpp>
#include <artificialIntelligence/classes/Basic3DWeightList.cpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;
using namespace artificialIntelligence::functions::layer;
using namespace artificialIntelligence::functions::activation;


// a weight list of lists of lists of Matrix3D<T>

template <typename T>
BasicLayer<T>::BasicLayer (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, Basic3DWeightList <T>* weights) {
   this->layerMatrix = new Matrix3D<T>(layerMatrix->getLength(), layerMatrix->getWidth(), layerMatrix->getHeight());
   this->layerMatrix->setMatrix(layerMatrix);
   if (biasMatrix != nullptr) {
      this->biasMatrix = new Matrix3D<T>(biasMatrix->getLength(), biasMatrix->getWidth(), biasMatrix->getHeight());
      this->biasMatrix->setMatrix(biasMatrix);
   } else {
      this->biasMatrix = nullptr;
   }
   this->weights = weights;
   this->next = nullptr;
   this->prev = nullptr;
}

template <typename T>
BasicLayer<T>::BasicLayer (int length, int width, int height) {
   this->layerMatrix = new Matrix3D<T> (length, width, height);
   this->layerMatrix->randomize();

   this->biasMatrix = new Matrix3D<T> (length, width, height);
   this->biasMatrix->randomize();

   this->weights = nullptr;
   this->next = nullptr;
   this->prev = nullptr;
}

template <typename T>
BasicLayer<T>::BasicLayer () {
   this->layerMatrix = nullptr;
   this->biasMatrix = nullptr;
   this->weights = nullptr;
   this->next = nullptr;
   this->prev = nullptr;
}

// template <typename T>
// BasicLayer<T>::~BasicLayer () {
//    if (this->next != nullptr) {
//       delete this->next;
//    }
// }

template <typename T>
int BasicLayer<T>::print (bool printBias, bool printWeights, int depth) {
   std::cout << "\n\nCurrent Index: " << depth << '\n';
   std::cout << "Layer Matrix: \n";
   this->layerMatrix->printMatrix();
   if (printBias) {
      std::cout << "Bias Matrix: \n";
      this->biasMatrix->printMatrix();
   }
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
   depth = this->next->print(printBias, printWeights, depth + 1);
   return depth;
}  

//if it hits the end, it adds a new one to the back of the list and then
//returns the newly added node, along with a way to tell the previous node the weights needed
template <typename T>
BasicLayer<T>* BasicLayer<T>::add (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, Basic3DWeightList<T>* weights) {

   if (next == nullptr) {
      this->next = new BasicLayer (layerMatrix, biasMatrix, weights);
      this->next->setPrev(this);
      this->biasMatrix = biasMatrix;
      this->weights = newWeight(this, this->next);
      return this;
   }
   this->next->add(layerMatrix, biasMatrix, weights);
   return this;
}

template <typename T>
void BasicLayer<T>::calculateAndUpdateAll () {
   if (next == nullptr) {
      return;
   }
   this->calculateAndUpdateSingle();
   this->next->calculateAndUpdateAll();
}

template <typename T>
void BasicLayer<T>::calculateAndUpdateSingle () {
   // start with the first node, and add all of the values to a node then sigmoid
   Matrix3D<T>* nextLayer = this->next->getLayerMatrix();
   Matrix3D<T>* outputs = new Matrix3D<T> (nextLayer->getLength(), nextLayer->getWidth(), nextLayer->getHeight());
   if (isnan(outputs->getData(0, 0, 0))) {
      std::cout << "null init";
      exit (0);
   }
   
   // declaring temp variables
   Matrix3D<T>* weights;
   float activation = 0;

            // loop through every weight matrix
   for (int fl = 0; fl < this->layerMatrix->getLength(); fl++) {
      for (int fw = 0; fw < this->layerMatrix->getWidth(); fw++) {
         for (int fh = 0; fh < this->layerMatrix->getHeight(); fh++) {

            // making the activation start at the bias point
            // this returns the matrix for each node
            // now the matrix needs to be factored into each 
            weights = this->weights->getWeightMatrix(fl, fw, fh);
         
            for (int sl = 0; sl < nextLayer->getLength(); sl++) {
               for (int sw = 0; sw < nextLayer->getWidth(); sw++) {
                  for (int sh = 0; sh < nextLayer->getHeight(); sh++) {
                     // weights->getData(sl, sw, sh);
                     // this is the weight which corresponds to the input node and the output node
                     // this->layerMatrix->getData(fl, fw, fh);
                     // this is the data which corresponds to the input node
                     // outputs->getData(sl, sw, sh);
                     // this is the current value in the node
                     activation = this->layerMatrix->getData(fl, fw, fh) * weights->getData(sl, sw, sh) + outputs->getData(sl, sw, sh);
                     if (isnan(activation)) {
                        std::cout << this->layerMatrix->getData(fl, fw, fh) << " ";
                        std::cout << weights->getData(sl, sw, sh) << " ";
                        std::cout << outputs->getData(sl, sw, sh) << " ";
                        outputs->printMatrix();
                        std::cout << "\n" << sl << " " << sw << " " << sh;
                        std::cout << "\nactivation\n";
                        exit (0);
                     }
                     outputs->insert(activation, sl, sw, sh);
                  }
               }
            }
            // weights->
            
         }
      }
   }
   
   // adds the bias and takes the sigmoid
   for (int sl = 0; sl < nextLayer->getLength(); sl++) {
      for (int sw = 0; sw < nextLayer->getWidth(); sw++) {
         for (int sh = 0; sh < nextLayer->getHeight(); sh++) {
            activation = sigmoid (outputs->getData(sl, sw, sh) + this->biasMatrix->getData(sl, sw, sh));
            outputs->insert(activation, sl, sw, sh);
         }
      }
   }

   // set the next matrix to the layer that was just found
   this->next->setLayerMatrix (outputs);
   delete outputs;

}

template <typename T>
void BasicLayer<T>::setPrev (BasicLayer<T>* prev) {
   if (this->prev != nullptr) {
      delete this->prev;
   }
   this->prev = prev;
}

template <typename T>
Matrix3D<T>* BasicLayer<T>::getLayerMatrix () {
   return this->layerMatrix;
}

template <typename T>
void BasicLayer<T>::setLayerMatrix (Matrix3D<T>* layerMatrix) {
   if (this->layerMatrix == nullptr) {
      this->layerMatrix = new Matrix3D<T> (layerMatrix->getLength(), layerMatrix->getWidth(), layerMatrix->getHeight());
   }
   this->layerMatrix->setMatrix(layerMatrix);
}

template <typename T>
Matrix3D<T>* BasicLayer<T>::getWeights (int length, int width, int height) {
   return this->weights->getWeightMatrix(length, width, height);
}

// template <typename T>
// void BasicLayer<T>::setWeights (BasicWeight<T>* weights) {
//    if (this->weights != nullptr) {
//       this->weights->setMatrix(&weights);
//    } else {
//       this->weights->setMatrix (weights);
//       this->weights = weights;
//    }
// }

template <typename T>
Matrix3D<T>* BasicLayer<T>::getBias () {
   return this->biasMatrix;
}

template <typename T>
void BasicLayer<T>::setBiasMatrix (Matrix3D<T>* biasMatrix) {
   if (this->biasMatrix == nullptr) {
      this->biasMatrix = new Matrix3D<T> (biasMatrix->getLength(), biasMatrix->getWidth(), biasMatrix->getHeight());
   }
   this->biasMatrix->setMatrix(biasMatrix);
}

template <typename T>
BasicLayer<T>* BasicLayer<T>::getLast () {
   if (this->next == nullptr) {
      return this;
   }
   return this->next->getLast();
}

template <typename T>
BasicLayer<T>* BasicLayer<T>::getNext () {
   return this->next;
}

template <typename T>
BasicLayer<T>* BasicLayer<T>::getPrev () {
   return this->prev;
}

#endif