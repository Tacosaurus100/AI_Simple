#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <coreutils/functions/debug/print.cpp>

namespace coreutils {
   namespace classes {
      namespace matrixes {
         template <typename T>
         class Matrix {
            public:
               void operator += (const Matrix& m2);
               void operator -= (const Matrix& m2);
               Matrix operator + (const Matrix& m2);
               Matrix operator - (const Matrix& m2);
               void printMatrix ();
         };
      }
   }
}

#endif