#ifndef MATRIX3D
#define MATRIX3D

#include <iostream>
#include <random>
#include <cmath>
#include <coreutils/functions/debug/print.cpp>
#include <coreutils/classes/matrixes/Matrix.cpp>
#include <coreutils/functions/sort/sortHelpers.cpp>
#include <coreutils/functions/math/simpleMath.cpp>

using namespace coreutils::functions;

namespace coreutils {
   namespace classes {
      namespace matrixes {
         template <typename T>
         class Matrix3D : public coreutils::classes::matrixes::Matrix<T>{
            private:
               // length is first, then width, then height
               int length;
               int width;
               int height;
               T*** arr;

            public:

               int getLength () {
                  return this->length;
               }

               int getWidth () {
                  return this->width;
               }

               int getHeight () {
                  return this->height;
               }

               T getData (int length, int width, int height) {
                  if (this->length <= length || this->width <= width || this->height <= height) {
                     std::cout << "Invalid input at getData";
                  }
                  return this->arr[length][width][height];
               }

               // shuffles every single value
               void shuffleEvery () {
                  for (int length = 0; length < this->length; length++) {
                     for (int width = 0; width < this->width; width++) {
                        for (int height = 0; height < this->height; height++) {
                           sort::swap (&this->arr[length][width][height], 
                                       &this->arr 
                                       [(int) math::rand(0, this->length - 1)]
                                       [(int) math::rand(0, this->width - 1)]
                                       [(int) math::rand(0, this->height - 1)]);

                        }
                     }
                  }
               }


               // shuffles every 2d matrix. while retaining the 2d matrix
               int* shuffleGroups () {
                  int* order = new int[this->length];
                  for (int length = 0; length < this->length; length++) {
                     int randomLength = (int) math::rand(0, this->length - 1);
                     order[length] = randomLength;
                     for (int width = 0; width < this->width; width++) {
                        for (int height = 0; height < this->height; height++) {
                           sort::swap (&this->arr [length][width][height], 
                                       &this->arr [randomLength][width][height]);

                        }
                     }
                  }
                  return order;
               }

               void shuffleGroups (int* order) {
                  for (int length = 0; length < this->length; length++) {
                     for (int width = 0; width < this->width; width++) {
                        for (int height = 0; height < this->height; height++) {
                           sort::swap (&this->arr [length][width][height], 
                                       &this->arr [order[length]][width][height]);

                        }
                     }
                  }
               }

               // -- -- //

               // adds this and another matrix and 
               // sets this matrix equal to it
               void operator += (const Matrix3D& m2) {
                  for (int i = 0; i < length; i++) {
                     for (int j = 0; j < width; j++) {
                        for (int k = 0; k < height; k++) {
                           this->arr [i][j][k] += m2->arr [i][j][k];
                        }
                     }
                  }
               }

               // subtracts this and another matrix and 
               // sets this matrix equal to it
               void operator -= (const Matrix3D& m2) {
                  for (int i = 0; i < length; i++) {
                     for (int j = 0; j < width; j++) {
                        for (int k = 0; k < height; k++) {
                           this->arr [i][j][k] += m2->arr [i][j][k];
                        }
                     }
                  }
               }


               // returns addition of this and another matrix
               Matrix3D* operator + (const Matrix3D& m2) {
                  Matrix3D<double>* M3D = new Matrix3D (this->length, this->width, this->height);

                  for (int i = 0; i < length; i++) {
                     for (int j = 0; j < width; j++) {
                        for (int k = 0; k < height; k++) {
                           M3D->arr[i][j][k] = this->arr [i][j][k] + m2.arr [i][j][k];
                        }
                     }
                  }

                  return M3D;
               }

               // returns subtraction of this and another matrix
               Matrix3D* operator - (const Matrix3D& m2) {
                  Matrix3D<double>* M3D = new Matrix3D (this->length, this->width, this->height);

                  for (int i = 0; i < length; i++) {
                     for (int j = 0; j < width; j++) {
                        for (int k = 0; k < height; k++) {
                           M3D->arr[i][j][k] = this->arr [i][j][k] - m2.arr [i][j][k];
                        }
                     }
                  }
                  
                  return M3D;
               }

               void randomize () {
                  // RNG stuff that i dont understand
                  std::mt19937_64 rng;
                  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
                  rng.seed(ss);
                  std::uniform_real_distribution<double> unif(0, 1);

                  // input the rng values into array
                  double currentRandomNumber;
                  for (int i = 0; i < this->length; i++) {
                     for (int j = 0; j < this->width; j++) {
                        for (int k = 0; k < this->height; k++) {
                           currentRandomNumber = unif(rng);
                           arr [i][j][k] = currentRandomNumber;
                        }
                     }
                  }
               }

               double dotProduct (const Matrix3D* m2) {
                  double output = 0;
                  
                  for (int i = 0; i < length; i++) {
                     for (int j = 0; j < width; j++) {
                        for (int k = 0; k < height; k++) {
                           output += this->arr [i][j][k] * m2->arr [i][j][k];
                        }
                     }
                  }
                  
                  return output;
               }

               void insert (T data, int length, int width, int height) {
                  this->arr[length][width][height] = data;
               }

               void printMatrix () {
                  std::cout << '\n' << "{";
                  for (int i = 0; i < this->length; i++) {
                     std::cout << '\n' << "  {" << '\n';
                     for (int j = 0; j < this->width; j++) {
                        std::string out = "    {";
                        for (int k = 0; k < this->height; k++) {
                           out += std::to_string(this->arr [i][j][k]) + ", ";
                        }
                        out = out.substr(0, out.length () - 3);
                        std::cout << out << "}" << '\n';
                     }
                     std::cout << "  }";
                  }
                  std::cout << '\n' << "}" << '\n';
               }

               // Matrix3D (int length, int width, int height) {
               //    this->length = length;
               //    this->width = width;
               //    this->height = height;
               //    // this->arr = new T [length][width][height];
               //    T*** l = new T** [length];
               //    for (int i = 0; i < length; i++) {
               //       l[i] = new T* [width];
               //       for (int j = 0; j < width; j++) {
               //          l[i][j] = new T [height];
               //       }
               //    }

               //    this->arr = l;
               // }

               Matrix3D (const int length, const int width, const int height) {
                  this->length = length;
                  this->width = width;
                  this->height = height;
                  // this->arr = new T [length][width][height];
                  T*** l = new T** [length];
                  for (int i = 0; i < length; i++) {
                     l[i] = new T* [width];
                     for (int j = 0; j < width; j++) {
                        l[i][j] = new T [height];
                     }
                  }

                  this->arr = l;
               }

               Matrix3D () {
                  this->length = 0;
                  this->width = 0;
                  this->height = 0;
                  T*** l = new T** [length];
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
}

#endif