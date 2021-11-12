#include <sys/time.h>
#include <sys/resource.h>

#include <artificialIntelligence/functions/images/generateInput.cpp>
#include <artificialIntelligence/basicLearningTypes/generationalAIBasic.cpp>
#include <artificialIntelligence/classes/BasicLayerList.cpp>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

using namespace std;
using namespace artificialIntelligence::functions;
using namespace coreutils::classes::matrixes;

int main () {
   std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
   std::cout << std::fixed;
   std::cout << std::setprecision(2);

   int epochs = 50;
   double learningRate = 0.05;
   int hiddenLayerLength = 1; 
   int hiddenLayerWidth = 2;
   int hiddenLayerHeight = 16;

   // layerCount - 2 = hiddenLayerCount
   int layerCount = 4;

   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../../artificialIntelligence/neuralNetworks";
   filesystem::current_path(filesystem::path(*currentPath));

   string inputImageFolder;
   delete currentPath;

   int inputCount = 0;
   for (int i = 0; i < 10; i++) {
      inputImageFolder = (string) filesystem::current_path() + "/../data/images/mnist_png/training/" + std::to_string(i) + '/';
      // loop to go through each file
      for (const auto & entry : filesystem::directory_iterator(inputImageFolder)) {
         inputCount++;
      }
   }

   Matrix3D<float>** inputMatrixes = new Matrix3D<float>* [inputCount];
   Matrix3D<float>** outputMatrixes = new Matrix3D<float>* [inputCount];

   // Matrix3D<char>* listOfInputs = new Matrix3D<char> []
   // loop to go through each folder
   int startOfDirectoryIndex = 0;
   for (int i = 0; i < 10; i++) {
      inputImageFolder = (string) filesystem::current_path() + "/../data/images/mnist_png/training/" + std::to_string(i) + '/';
      // loop to go through each file
      int counter = 0;
      for (const auto & entry : filesystem::directory_iterator(inputImageFolder)) {
         std::cout << entry.path() << std::endl;
         // convImage->printMatrix();
         inputMatrixes[startOfDirectoryIndex + counter] = images::generate::inputMatrixNormalized(entry.path(), "RGBA");
         // if (counter == 3) {
         //    exit (0);
         // }
         Matrix3D<float>* output = new Matrix3D<float> (1, 1, 10);
         output->insert(1, 0, 0, i);
         outputMatrixes[startOfDirectoryIndex + counter] = output;
         counter++;
      }
      startOfDirectoryIndex = counter + startOfDirectoryIndex;
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

   // inputMatrixes [10]->printMatrix();
   // inputMatrixes [20]->printMatrix();
   // inputMatrixes [30]->printMatrix();
   // inputMatrixes [40]->printMatrix();
   // inputMatrixes [50]->printMatrix();
   // outputMatrixes [10]->printMatrix();
   // outputMatrixes [20]->printMatrix();
   // outputMatrixes [30]->printMatrix();
   // outputMatrixes [40]->printMatrix();
   // outputMatrixes [50]->printMatrix();

   artificialIntelligence::basicLearningTypes::generationalAIBasic::run(list, epochs, learningRate, inputMatrixes, outputMatrixes, inputCount);

   // inputMatrixes [10]->printMatrix();
   // inputMatrixes [20]->printMatrix();
   // inputMatrixes [30]->printMatrix();
   // inputMatrixes [40]->printMatrix();
   // inputMatrixes [50]->printMatrix();
   // outputMatrixes [10]->printMatrix();
   // outputMatrixes [20]->printMatrix();
   // outputMatrixes [30]->printMatrix();
   // outputMatrixes [40]->printMatrix();
   // outputMatrixes [50]->printMatrix();
   list->toFile ((string) filesystem::current_path() + "/../data/images/mnist_png/mnistTrainedModelLargeSet2.csv");



   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   std::cout << "\nMemory used (MB): " << usage.ru_maxrss / 1000 << "\n\n";
}