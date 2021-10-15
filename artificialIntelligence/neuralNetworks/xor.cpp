#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <coreutils/functions/math/simpleMath.cpp>
#include <coreutils/functions/procedural/stringFunctions.cpp>

#include <artificialIntelligence/basicLearningTypes/generationalAIBasic.cpp>

using namespace std;
using namespace coreutils::functions;

int main () {
   std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
   
   //int epochs, int learningRate, Matrix3D<double> firstMatrix, int hiddenLayers, int** hiddenLayerCount, string inputData, string outputData) {
   
   int epochs = 2;
   double learningRate = 0.1;

   // needs to be at least two 
   int layerCount = 4;

   // get the file from the location
   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../artificialIntelligence/neuralNetworks";
   filesystem::current_path(filesystem::path(*currentPath));
   string inputData = filesystem::current_path();
   delete currentPath;
   inputData += "/../data/xorInputData.txt";
   
   fstream inputs;
   inputs.open(inputData, ios::in);
   string input;
   string output;


   int inputCount = 0;
   int inputSize = 0;
   int outputSize = 0;

   // get the number of lines in the file

   while (getline(inputs, input)) {
      getline (inputs, output);
      inputCount++;
   }
   procedural::split(input.substr(1, input.length() - 2), ",", &inputSize);
   procedural::split(output.substr(1, output.length() - 2), ",", &outputSize);

   Matrix3D<float>* inputMatrix = new Matrix3D<float> [inputCount];
   Matrix3D<float>* outputMatrix = new Matrix3D<float> [inputCount];

   for (int c = 0; c < inputCount; c++){
      inputMatrix[c] = Matrix3D<float> (1, inputSize, 1);
      inputMatrix[c].randomize();
      outputMatrix[c] = Matrix3D<float> (1, outputSize, 1);
      outputMatrix[c].randomize();
   }
   // reinitialize inputs and go thorugh it
   inputs.close();
   inputs.open(inputData, ios::in);
   inputCount = 0;
   while (getline (inputs, input)){
      getline (inputs, output);

      // go through inputs and add them to a matrix
      vector<string>* split = procedural::split(input.substr(1, input.length() - 2), ",");
      for (int i = 0; i < inputSize; i++) {
         inputMatrix[inputCount].insert(stof(split->at(i)), 0, i, 0);
      }

      // go through outputs and add them to a matrix
      split = procedural::split(output.substr(1, output.length() - 2), ",");
      for (int i = 0; i < outputSize; i++) {
         outputMatrix[inputCount].insert(stof(split->at(i)), 0, i, 0);
      }
      inputCount++;
   }

   if (inputCount == 0) {
      cout << "Invalid data file";
      exit(1);
   }

   // for (int i = 0; i < inputCount; i++) {
   //    cout << "Input Matrixes " << i << ":";
   //    inputMatrix[i].printMatrix();
   //    cout << "Output Matrix " << i << ":";
   //    outputMatrix[i].printMatrix();
   // }
   artificialIntelligence::basicLearningTypes::generationalAIBasic::run(epochs, learningRate, inputMatrix, outputMatrix, inputCount, layerCount - 2);

   for (int i = 0; i < inputCount; i++) {
      cout << "Input Matrixes " << i << ":";
      inputMatrix[i].printMatrix();
      cout << "Output Matrix " << i << ":";
      outputMatrix[i].printMatrix();
   }

   // Matrix3D<double>* m3d = new Matrix3D<double> (inputCount, 1, 1);
   // m3d->randomize();


   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
}