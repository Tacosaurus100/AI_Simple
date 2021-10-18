#ifndef ACTIVATION_FUNCTIONS_HPP
#define ACTIVATION_FUNCTIONS_HPP

#include <cmath>
#include <coreutils/classes/matrixes/Matrix3D.cpp>

using namespace coreutils::classes::matrixes;

namespace artificialIntelligence {
   namespace functions {
      namespace activation {
         // sigmoid function
         double sigmoid (double x);

         // derivative of the sigmoid function
         double dSigmoid (double x);

         // sigmoid function for entire matrix
         template <typename T>
         Matrix3D<T>* sigmoid (Matrix3D<T>* m3d);

         // derivative of the sigmoid function for entire matrix
         template <typename T>
         Matrix3D<T>* dSigmoid (Matrix3D<T>* m3d);

         //sigmoid function
         double tanh (double x);

         // derivative of the tanH function
         double dTanh (double x);

         // tanh function for entire matrix
         template <typename T>
         Matrix3D<T>* tanh (Matrix3D<T>* m3d);

         // derivative of the tanh function for entire matrix
         template <typename T>
         Matrix3D<T>* dTanh (Matrix3D<T>* m3d);
      }
   }
}

#endif