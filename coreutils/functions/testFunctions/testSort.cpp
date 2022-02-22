#include <iostream>
#include <coreutils/functions/sort/sort.h>

using namespace coreutils::functions;

const int arrSize = 14;

void testInsert () {
   std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
   
   int testInsert [arrSize] = {3, 7, 5, 2, 4, 6, 9, 10, 12, 1, 2, 3, 4, 5}; 

   debug::printArr (testInsert, arrSize);
   int* order = sort::insertionSort (testInsert, arrSize);
   debug::printArr (testInsert, arrSize);
   debug::printArr (order, arrSize);

   coreutils::functions::sort::reverse (testInsert, arrSize);
   debug::printArr (testInsert, arrSize);

   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
}

void testMerge () {
   std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();

   int testMerge [14] = {3, 7, 5, 2, 4, 6, 9, 10, 12, 1, 2, 3, 4, 5}; 
   debug::printArr (testMerge, arrSize);
   sort::mergeSort (testMerge, 0, arrSize - 1);
   debug::printArr (testMerge, arrSize);

   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
}

int main () {
   testInsert ();
   testMerge ();
}