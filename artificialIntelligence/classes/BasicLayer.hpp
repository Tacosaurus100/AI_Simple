#ifndef BASIC_LAYER_HPP
#define BASIC_LAYER_HPP

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/classes/Basic3DWeightList.hpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;

namespace artificialIntelligence {
   namespace classes {

      template <typename T>
      class BasicLayer{
         private:
            Matrix3D<T>* layerMatrix;
            Matrix3D<T>* biasMatrix;
            BasicWeight<T>* weights;
            BasicLayer* next;
            BasicLayer* prev;

         public:
            BasicLayer (Matrix3D<T>* layerMatrix, Matrix3D<T>* biasMatrix = nullptr, BasicWeight<T>* weights = nullptr);

            BasicLayer (int length, int width, int height);

            BasicLayer ();

            ~BasicLayer ();

            int print (bool printBias = false, bool printWeights = false, int depth = 1);

            BasicLayer<T>* add (BasicLayer<T>* layer);

            BasicLayer<T>* add (Matrix3D<T>* layer, Matrix3D<T>* biasMatrix = nullptr, BasicWeight<T>* weights = nullptr);

            void calculateAndUpdateAll ();

            void calculateAndUpdateSingle ();

            void setPrev (BasicLayer<T>* prev);

            Matrix3D<T>* getLayerMatrix ();

            void setLayerMatrix (Matrix3D<T>* layerMatrix);

            Matrix3D<T>* getWeights (int length, int width, int height);

            // void setWeights (BasicWeight<T> weights);

            Matrix3D<T>* getBias ();

            void setBiasMatrix (Matrix3D<T>* bias);

            BasicLayer<T>* getLast ();

            BasicLayer<T>* getNext ();

            BasicLayer<T>* getPrev ();

            void toFile (std::ofstream* outputFile);
            
            static BasicLayer<T>* loadFromFile (std::ifstream* inputFile, BasicLayer<T>* prev = nullptr);
      };
   }
}
#endif