namespace coreutils 
{
   namespace functions
   {
      namespace sort {
         // swaps two values in array
         template <typename T>
         void swap (T* first, T* second);

         // shuffles array
         template <typename T>
         void shuffle (T* arr, int size);

         // reverses array
         template <typename T>
         void reverse (T* arr, int size);

         // uses insertionSort to sort
         // returns the new order of the array
         template <typename T>
         int* insertionSort (T* arrayPtr, int size);

         // uses mergeSort to sort
         template <typename T>
         void merge(T *Arr, int start, int mid, int end);

      }
   }
}