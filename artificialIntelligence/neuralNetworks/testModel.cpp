#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/layerFunctions.cpp>
#include <artificialIntelligence/functions/activationFunctions.cpp>
#include <artificialIntelligence/classes/Basic3DWeightList.hpp>
#include <artificialIntelligence/classes/BasicWeight.cpp>
#include <artificialIntelligence/classes/BasicLayerList.hpp>


using namespace std;

int main () {
   
   ifstream in;
   in.open("artificialIntelligence/data/multsub1dataweights.txt");
   string line;
   if (in.is_open()) {

      int layerIndex = 0;
      while (getline (in,line)) {
         if (line.find("Current Index") == 0){
            line = line.substr(15);
            layerIndex = stoi(line);
         }
         else if (line.find("Layer Matrix") == 0){
            coreutils::classes::Matrix3D::findAndMakeMatrix ();

         cout << line << '\n';
      }
      in.close();
   }

}

