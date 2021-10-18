#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

int main () {
   
   std::ofstream out("multsub1data.txt");


   for (int i = 1; i <= 10; i++) {
      for (int j = 1; j <= 10; j++) {
         if (i == 10 && j != 10) {
            out << "[1.0f,0." << j << "f]\n";
         } else if (i != 10 && j == 10) {
            out << "[0." << i << "f,1.0f]\n";
         } else if (i == 10 && j == 10) {
            out << "[1.0f,1.0f]\n";
         } else {
            out << "[0." << i << "f,0." << j << "f]\n";
         }
         out << "[" << (i * j - 1) / (float)100 << "f]\n";
      }
   }

   out.close();
   return 0;
}