
#ifndef FILE_TO_ARRAY
#define FILE_TO_ARRAY

#include <iostream>
#include <fstream>
#include <string>


namespace coreutils 
{
   namespace functions
   {
      namespace sort {
         // builds a 2d array based on values from a file
         void buildArray (int** ptr);

         void buildArray (int** ptr) {
            std::fstream newfile;
            newfile.open("triangleSumInput.txt",std::ios::in);
            if (newfile.is_open()) {
               std::string tp;
               int temp;
               int num;
               int* tempPtr;
               while(getline(newfile, tp)) {
                  num = 0;
                  tempPtr = *ptr; 
                  for (char x : tp){
                     if (x == ' ') {
                        *tempPtr = num;
                        num = 0;
                        tempPtr++;
                     } else {
                        num *= 10;
                        num += x - '0';
                     }
                  }
                  *tempPtr = num;
                  ptr++;
               }
               newfile.close(); //close the file object.
            }
         }
      }
   }
}

#endif