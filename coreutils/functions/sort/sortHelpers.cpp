#ifndef SORTHELPERS
#define SORTHELPERS

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <coreutils/functions/math/simpleMath.cpp>

using namespace coreutils::functions;

namespace coreutils 
{
   namespace functions
   {
      namespace sort {
         //swaps the two valus given
         template <typename T>
         void swap (T* first, T* second);

         template <typename T>
         void shuffle (T* arr, int size);

         template <typename T>
         void swap (T* first, T* second){
            T temp = *first;
            *first = *second;
            *second = temp;
         }

         template <typename T>
         void shuffle (T* arr, int size) {
            for (int i = 0; i < size; i++) {
               coreutils::functions::sort::swap (&arr[i], &arr[(int) math::rand(0, size - 1)]);
            }
         }
      }
   }
}

#endif