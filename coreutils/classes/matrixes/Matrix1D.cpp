#ifndef MATRIX1D
#define MATRIX1D

#include <iostream>
#include <coreutils/classes/matrixes/Matrix.cpp>

namespace coreutils {
   namespace classes {
      template <typename T>
      class Matrix1D : public coreutils::classes::Matrix<T> {
         public:
            T arr [];

            void printMatrix () {
               
            }
      };
   }
}

#endif