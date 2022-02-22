#ifndef BASIC_LAYER
#define BASIC_LAYER

#include <iostream>
#include <string>
#include <sstream>
#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/layerFunctions.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>
#include <artificialIntelligence/classes/BasicLayer.hpp>
#include <artificialIntelligence/classes/BasicWeight.cpp>

using namespace std;
using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;
using namespace artificialIntelligence::functions::layer;
using namespace artificialIntelligence::functions::activation;


// a weight list of lists of lists of Matrix3D<T>

template <typename T>
BasicLayer<T>::BasicLayer (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, BasicWeight<T>* weights) {
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
   this->biasMatrix = nullptr;
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

template <typename T>
BasicLayer<T>::~BasicLayer () { 
   if (this->layerMatrix != nullptr) {
      delete this->layerMatrix;
   }
   if (this->biasMatrix != nullptr) {
      delete this->biasMatrix;
   }
   if (this->weights != nullptr) {
      delete this->weights;
   }
   if (this->prev != nullptr) {
      this->prev->next = this->next;
   }
}

// template <typename T>
// BasicLayer<T>::~BasicLayer () {
//    if (this->next != nullptr) {
//       delete this->next;
//    }
// }

template <typename T>
int BasicLayer<T>::print (bool printBias, bool printWeights, int depth) {
   if (this->layerMatrix != nullptr) {
      std::cout << "\n\nCurrent Index: " << depth << '\n';
      std::cout << "Layer Matrix: \n";
      this->layerMatrix->printMatrix();
   } else {
      std::cout << "No layer found!\n";
      return depth;
   }
   if (printBias) {
      if (this->biasMatrix != nullptr) {
         std::cout << "Bias Matrix: \n";
         this->biasMatrix->printMatrix();
      } else {
         std::cout << "No biases found!\n";
      }
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
   return this->next->print(printBias, printWeights, depth + 1);;
}  

//if it hits the end, it adds a new one to the back of the list and then
//returns the newly added node, along with a way to tell the previous node the weights needed
template <typename T>
BasicLayer<T>* BasicLayer<T>::add (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix, BasicWeight<T>* weights) {

   if (next == nullptr) {
      this->next = new BasicLayer (layerMatrix, nullptr, nullptr);
      this->next->setPrev(this);
      if (this->biasMatrix == nullptr) {
         // std::cout << this->next->layerMatrix->getLength() << " " << this->next->layerMatrix->getWidth() << " " << this->next->layerMatrix->getHeight();
         this->biasMatrix = new Matrix3D<T>(this->next->layerMatrix->getLength(), this->next->layerMatrix->getWidth(), this->next->layerMatrix->getHeight());
         this->biasMatrix->randomize(-0.05, 0.05);
      } else {
         this->biasMatrix->setMatrix(biasMatrix);
      }

      this->weights = newWeight(this, this->next);
      return this;
   }
   this->next->add(layerMatrix, biasMatrix, weights);
   return this;
}

template <typename T>
BasicLayer<T>* BasicLayer<T>::add (BasicLayer<T>* layer) {
   if (this->next == nullptr) {
      this->next = layer;
   } else {
      this->next = this->next->add(layer);
   }
   return this;
}

template <typename T>
void BasicLayer<T>::calculateAndUpdateAll () {
   if (this->next == nullptr) {
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
   if (isnan(*outputs->getData(0, 0, 0))) {
      std::cout << "null init";
      exit (0);
   }
   // start at start layer, then go to the end layer
   
   // declaring temp variables
   Matrix3D<T>* weights;
   float activation = 0;

   // loop through every weight matrix
   // std::cout << "[" << this->layerMatrix->getLength() << "] " << "[" << this->layerMatrix->getWidth() << "] " << "[" << this->layerMatrix->getHeight() << "]   " 
   // << "[" << nextLayer->getLength() << "] " << "[" << nextLayer->getWidth() << "] " << "[" << nextLayer->getHeight() << "]" << "\n\n";
   for (int fl = 0; fl < this->layerMatrix->getLength(); fl++) {
      for (int fw = 0; fw < this->layerMatrix->getWidth(); fw++) {
         for (int fh = 0; fh < this->layerMatrix->getHeight(); fh++) {
            
            // making the activation start at the bias point
            // this returns the matrix for each node
            // now the matrix needs to be factored into each 
            weights = this->weights->getWeightMatrix(fl, fw, fh);
         
            // std::cout << "[" << fl << "] " << "[" << fw << "] " << "[" << fh << "] " << '\n';

            // if (fw == 1) {
            //    if (weights == nullptr) {
            //       this->weights->print();
            //       layerMatrix->printMatrix();
            //       std::cout << "error";
            //       exit (0);
            //    }
            //    weights->printMatrix();
            // }

            for (int sl = 0; sl < nextLayer->getLength(); sl++) {
               for (int sw = 0; sw < nextLayer->getWidth(); sw++) {
                  for (int sh = 0; sh < nextLayer->getHeight(); sh++) {
                     
                     // if (isnan(activation)) {
                     //    std::cout << this->layerMatrix->getData(fl, fw, fh) << " ";
                     //    std::cout << weights->getData(sl, sw, sh) << " ";
                     //    std::cout << outputs->getData(sl, sw, sh) << " ";
                     //    outputs->printMatrix();
                     //    std::cout << "\n" << sl << " " << sw << " " << sh;
                     //    std::cout << "\nactivation\n";
                     //    exit (0);
                     // }
                     
                     activation = *this->layerMatrix->getData(fl, fw, fh) * *weights->getData(sl, sw, sh) + *outputs->getData(sl, sw, sh);

                     // std::cout << "[" << fl << "] " << "[" << fw << "] " << "[" << fh << "]   " << "[" << sl << "] " << "[" << sw << "] " << "[" << sh << "]" << '\n';
                        
                     // std::cout << this->layerMatrix->getData(fl, fw, fh) << "    " << weights->getData(sl, sw, sh) << "   " << activation <<  '\n';
                     outputs->insert(activation, sl, sw, sh);
                  }
               }
            }
         }
      }
   } 

   // adds the bias and takes the sigmoid
   for (int sl = 0; sl < nextLayer->getLength(); sl++) {
      for (int sw = 0; sw < nextLayer->getWidth(); sw++) {
         for (int sh = 0; sh < nextLayer->getHeight(); sh++) {
            activation = sigmoid(*outputs->getData(sl, sw, sh) + *this->biasMatrix->getData(sl, sw, sh));
            // std::cout << outputs->getData(sl, sw, sh) << '\n';
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

template <typename T>
void BasicLayer<T>::toFile (std::ofstream* outputFile) {
   *outputFile << this->layerMatrix->getLength() << ',' << this->layerMatrix->getWidth() << ',' << this->layerMatrix->getHeight() << '\n';

   // print bias values
   if (this->biasMatrix == nullptr) {
      return;
   }
   *outputFile << this->biasMatrix->getLength() << ',' << this->biasMatrix->getWidth() << ',' << this->biasMatrix->getHeight() << '\n';
   for (int i = 0; i < this->biasMatrix->getLength(); i++) {
      for (int j = 0; j < this->biasMatrix->getWidth(); j++) {
         for (int k = 0; k < this->biasMatrix->getHeight(); k++) {
            *outputFile << *this->biasMatrix->getData(i, j, k) << ',';
         }
      }
   }

   outputFile->seekp((int) outputFile->tellp() - 1);
   outputFile->write("\n", 1);

   if (this->weights == nullptr) {
      return;
   }

   // print weight values
   *outputFile << this->layerMatrix->getLength() << ',' << this->layerMatrix->getWidth() << ',' << this->layerMatrix->getHeight() << ',';
   *outputFile << this->biasMatrix->getLength() << ',' << this->biasMatrix->getWidth() << ',' << this->biasMatrix->getHeight() << '\n';
   for (int l = 0; l < this->layerMatrix->getLength(); l++) {
      for (int w = 0; w < this->layerMatrix->getWidth(); w++) {
         for (int h = 0; h < this->layerMatrix->getHeight(); h++) {
            for (int l2 = 0; l2 < this->biasMatrix->getLength(); l2++) {
               for (int w2 = 0; w2 < this->biasMatrix->getWidth(); w2++) {
                  for (int h2 = 0; h2 < this->biasMatrix->getHeight(); h2++) {
                     *outputFile << *this->weights->getData(l, w, h, l2, w2, h2) << ',';
                  }
               }
            }
         }
      }
   }

   outputFile->seekp((int) outputFile->tellp() - 1);
   outputFile->write("\n", 1); 

   if (this->next == nullptr) {
      return;
   }
   this->next->toFile(outputFile);
}

template <typename T>
BasicLayer<T>* BasicLayer<T>::loadFromFile (std::ifstream* inputFile, BasicLayer<T>* prev) {
   BasicLayer<T>* layer = new BasicLayer ();
   std::string line;
   getline (*inputFile, line);
   std::stringstream lineStream;
   lineStream << line;
   std::string value;
   getline(lineStream, value, ',');
   int layerLength = stoi(value);
   getline(lineStream, value, ',');
   int layerWidth = stoi(value);
   getline(lineStream, value, ',');
   int layerHeight = stoi(value);
   Matrix3D<T>* layerMatrix = new Matrix3D<T> (layerLength, layerWidth, layerHeight);
   layer->layerMatrix = layerMatrix;
   layer->prev = prev;
      // std::cout << layerLength << " " << layerWidth << " " << layerHeight;

   lineStream.str(std::string());
   lineStream.clear();
   getline (*inputFile, line);
   lineStream << line;

   if (inputFile->eof()) {
      layer->biasMatrix = nullptr;
      layer->weights = nullptr;
      return layer;
   }

   getline(lineStream, value, ',');
   int biasLength = stoi(value);
   getline(lineStream, value, ',');
   int biasWidth = stoi(value);
   getline(lineStream, value, ',');
   int biasHeight = stoi(value);
   Matrix3D<T>* biasMatrix = new Matrix3D<T> (biasLength, biasWidth, biasHeight);
   layer->biasMatrix = biasMatrix;

   lineStream.str(std::string());
   lineStream.clear();
   getline (*inputFile, line);
   lineStream << line;
   for (int i = 0; i < layer->biasMatrix->getLength(); i++) {
      for (int j = 0; j < layer->biasMatrix->getWidth(); j++) {
         for (int k = 0; k < layer->biasMatrix->getHeight(); k++) {
            std::getline(lineStream, value, ',');
            layer->biasMatrix->insert (stod(value), i, j, k);
         }
      }
   }

   getline (*inputFile, line);

   if (inputFile->eof()) {
      layer->weights = nullptr;
      return layer;
   }

   BasicWeight<T>* weights = new BasicWeight<T> (
      layer->layerMatrix->getLength(), 
      layer->layerMatrix->getWidth(), 
      layer->layerMatrix->getHeight(), 
      layer->biasMatrix->getLength(), 
      layer->biasMatrix->getWidth(), 
      layer->biasMatrix->getHeight()
   );

   
   lineStream.str(std::string());
   lineStream.clear();
   getline (*inputFile, line);
   lineStream << line;
   // exit (0);
   for (int l = 0; l < layerLength; l++) {
      for (int w = 0; w < layerWidth; w++) {
         for (int h = 0; h < layerHeight; h++) {
            for (int l2 = 0; l2 < biasLength; l2++) {
               for (int w2 = 0; w2 < biasWidth; w2++) {
                  for (int h2 = 0; h2 < biasHeight; h2++) {
                     std::getline(lineStream, value, ',');
                     weights->insert(stod(value), l, w, h, l2, w2, h2);
                  }
               }
            }
         }
      }
   }

   layer->weights = weights;
   layer->next = BasicLayer<T>::loadFromFile (inputFile, layer);

   return layer;
}



#endif