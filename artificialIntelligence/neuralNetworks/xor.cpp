#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <coreutils/functions/math/simpleMath.cpp>
#include <coreutils/functions/procedural/stringFunctions.cpp>

#include <artificialIntelligence/basicLearningTypes/generationalAIBasic.cpp>
#include <artificialIntelligence/basicLearningTypes/testGenerationalAIBasic.cpp>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;
using namespace coreutils::functions;

int main () {
   std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();

   //int epochs, int learningRate, Matrix3D<double> firstMatrix, int hiddenLayers, int** hiddenLayerCount, string inputData, string outputData) {

   int epochs = 10000;
   double learningRate = 0.1;
   int hiddenLayerLength = 3; 
   int hiddenLayerWidth = 3;
   int hiddenLayerHeight = 3;

   // needs to be at least to 
   int layerCount = 4;

   // get the file from the location
   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../../artificialIntelligence/neuralNetworks";
   filesystem::current_path(filesystem::path(*currentPath));
   string inputData = filesystem::current_path();
   delete currentPath;
   inputData += "/../data/multsub1/multsub1data.txt";
   
   fstream inputs;
   inputs.open(inputData, ios::in);
   string input;
   string output;


   int inputCount = 0;
   int inputSize = 0;
   int outputSize = 0;

   // get the number of lines in the file

   while (getline(inputs, input)) {
      if (inputs.eof()) {
         break;
      }
      getline (inputs, output);
      inputCount++;
   }
   procedural::split(input.substr(1, input.length() - 2), ",", &inputSize);
   procedural::split(output.substr(1, output.length() - 2), ",", &outputSize);

   Matrix3D<float>** inputMatrixes = new Matrix3D<float>* [inputCount];
   Matrix3D<float>** outputMatrixes = new Matrix3D<float>* [inputCount];
   
   for (int c = 0; c < inputCount; c++){
      inputMatrixes[c] = new Matrix3D<float> (1, inputSize, 1);
      outputMatrixes[c] = new Matrix3D<float> (1, outputSize, 1);
   }
   // reinitialize inputs and go thorugh it
   inputs.close();
   inputs.open(inputData, ios::in);
   inputCount = 0;
   while (getline (inputs, input)){
      if (inputs.eof()) {
         break;
      }
      getline (inputs, output);

      // go through inputs and add them to a matrix
      vector<string>* split = procedural::split(input.substr(1, input.length() - 2), ",");
      for (int i = 0; i < inputSize; i++) {
         inputMatrixes[inputCount]->insert(stof(split->at(i)), 0, i, 0);
      }

      // go through outputs and add them to a matrix
      split = procedural::split(output.substr(1, output.length() - 2), ",");
      for (int i = 0; i < outputSize; i++) {
         outputMatrixes[inputCount]->insert(stof(split->at(i)), 0, i, 0);
      }
      inputCount++;
   }

   inputs.close();

   if (inputCount == 0) {
      cout << "Invalid data file";
      exit(1);
   }

  
  


   BasicLayerList<float>* list = new artificialIntelligence::classes::BasicLayerList<float> ();

   // input layer
   list->add (inputMatrixes[0]);

   list->editRootMatrix(inputMatrixes[0]);
   // exit (0);
   // hidden layers
   for (int i = 0; i < layerCount - 2; i++) {
      list->addNew (hiddenLayerLength, hiddenLayerWidth, hiddenLayerHeight);
   }
   
   // this is the output layer
   list->addNew (outputMatrixes[0]->getLength(), outputMatrixes[0]->getWidth(), outputMatrixes[0]->getHeight());
   
   artificialIntelligence::basicLearningTypes::generationalAIBasic::run(list, epochs, learningRate, inputMatrixes, outputMatrixes, inputCount);


   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   std::cout << "\nMemory used (MB): " << usage.ru_maxrss / 1000000 << "\n\n";
}