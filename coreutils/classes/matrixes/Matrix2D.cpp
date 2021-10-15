#ifndef MATRIX2D
#define MATRIX2D

#include <iostream>
#include <coreutils/classes/matrixes/Matrix.cpp>

namespace coreutils {
   namespace classes {
      template <typename T>
      class Matrix2D : public coreutils::classes::Matrix<T>{
         public:
            T** arr;

            void operator += (const Matrix2D& m2) {
               for (int i = 0; i < length; i++) {
                  for (int j = 0; j < width; j++) {
                     this->arr [i][j] += m2->arr [i][j];
                  }
               }
            }

            // subtracts this and another matrix and 
            // sets this matrix equal to it
            void operator -= (const Matrix2D& m2) {
               for (int i = 0; i < length; i++) {
                  for (int j = 0; j < width; j++) {
                     this->arr [i][j] -= m2->arr [i][j];
                  }
               }
            }


            // returns addition of this and another matrix
            Matrix2D* operator + (const Matrix2D& m2) {
               Matrix2D<double>* M2D = new Matrix2D (this->length, this->width);

               for (int i = 0; i < length; i++) {
                  for (int j = 0; j < width; j++) {
                     M2D->arr[i][j] = this->arr [i][j] + m2.arr [i][j];
                  }
               }

               return M2D;
            }

            // makes a new Matrix3D of the certain size
            //then returns dot product.
            double dotProduct (const Matrix2D* m2) {
               double output = 0;
               
               for (int i = 0; i < length; i++) {
                  for (int j = 0; j < width; j++) {
                     output += this->arr [i][j] * m2->arr [i][j];
                  }
               }
               
               return output;
            }

            // returns subtraction of this and another matrix
             Matrix2D* operator - (const Matrix2D& m2) {
               Matrix2D<double>* M2D = new Matrix2D (this->length, this->width);

               for (int i = 0; i < length; i++) {
                  for (int j = 0; j < width; j++) {
                     M2D->arr[i][j] = this->arr [i][j] - m2.arr [i][j];
                  }
               }

               return M2D;
            }

            // makes a new Matrix3D of the certain size
            // then returns cross product.
            // Matrix2D crossProduct (const Matrix2D* m2) {
            //    Matrix2D M2D = new Matrix3D (this->length, this->width, this->height);

            //    for (int i = 0; i < length; i++) {
            //       for (int j = 0; j < width; j++) {
            //          M2D->arr[i][j] = this->arr [i][j] * m2->arr [i][j];
            //       }
            //    }
               
            //    return M2D;
            // }

            void printMatrix () {
               std::cout << '\n' << "{";
               for (int i = 0; i < this->length; i++) {
                  std::cout << '\n' << "  {" << ;
                  for (int j = 0; j < this->width; j++) {
                     
                     out += std::to_string(this->arr [i][j]) + ", ";
                  }
                  out = out.substr(0, out.length () - 3);
                  std::cout << "  }\n";
               }
               std::cout << '\n' << "}" << '\n';
            }


            Matrix2D (int length, int width, int height) {
               this->length = length;
               this->width = width;
               this->height = height;
               // this->arr = new T [length][width][height];
               T** l = new T* [length];
               for (int i = 0; i < length; i++) {
                  l[i] = new T* [width];
                  for (int j = 0; j < width; j++) {
                     l[i][j] = new T [height];
                  }
               }

               this->arr = l;
            }
      };
   }
}


#endif