#ifndef INSERTION_SORT
#define INSERTION_SORT

#include <coreutils/functions/sort/sortHelpers.cpp>
#include <coreutils/functions/debug/print.cpp>

namespace coreutils 
{
   namespace functions
   {
      namespace sort {
         // uses insertionSort to sort
         template<typename T>
         void insertionSort (T* arrayPtr, int size);

         // uses mergeSort to sort
         template<typename T>
         void merge(T *Arr, int start, int mid, int end);

         template<typename T>
         void insertionSort (T* arrayPtr, int size){
            int smallestIndex;
            int index;
            int index2;

            for (int i = 0; i < size; i++) {
               smallestIndex = i;
               for (int j = i + 1; j < size; j++) {
                  if (arrayPtr [smallestIndex] > arrayPtr [j]){
                     smallestIndex = j;
                  }
               }
               swap (&arrayPtr [i], &arrayPtr [smallestIndex]);
            }
         }

         template<typename T>
         void merge(T *Arr, int start, int mid, int end) {
            // create a temp array
            T temp[end - start + 1];

            // crawlers for both intervals and for temp
            int i = start, j = mid+1, k = 0;

            // traverse both arrays and in each iteration add smaller of both elements in temp 
            while(i <= mid && j <= end) {
               if(Arr[i] <= Arr[j]) {
                  temp[k] = Arr[i];
                  k += 1; i += 1;
               }
               else {
                  temp[k] = Arr[j];
                  k += 1; j += 1;
               }
            }

            // add elements left in the first interval 
            while(i <= mid) {
               temp[k] = Arr[i];
               k += 1; i += 1;
            }

            // add elements left in the second interval 
            while(j <= end) {
               temp[k] = Arr[j];
               k += 1; j += 1;
            }

            // copy temp to original interval
            for(i = start; i <= end; i += 1) {
               Arr[i] = temp[i - start];
            }
         }

         // Arr is an array of integer type
         // start and end are the starting and ending index of current interval of Arr
         template<typename T>
         void mergeSort(T *Arr, int start, int end) {
            if(start < end) {
               int mid = (start + end) / 2;
               mergeSort(Arr, start, mid);
               mergeSort(Arr, mid+1, end);
               merge(Arr, start, mid, end);
            }
         }
      }
   }
}

#endif