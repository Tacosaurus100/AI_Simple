// g++ -o testMnistNetwork testMnistNetwork.cpp -O2 -I ../../ --std=c++2a `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs`

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

   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../../artificialIntelligence/neuralNetworks";
   filesystem::current_path(filesystem::path(*currentPath));
   std::string dataSet = (string) filesystem::current_path() + "/../data/images/mnist_png/mnistTrainedModelLargeSet4";
   std::string csvFilePath = dataSet + ".csv";
   BasicLayerList<float>* list = BasicLayerList<float>::loadFromFile (csvFilePath);



   // string* currentPath = new string (filesystem::current_path());
   // *currentPath += "/../../artificialIntelligence/neuralNetworks";
   // filesystem::current_path(filesystem::path(*currentPath));

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
   std::string type;
   if (list->getRoot()->getLayerMatrix()->getLength() == 1) {
      type = "BW";
   } else if (list->getRoot()->getLayerMatrix()->getLength() == 3) {
      type = "RGB";
   } else if (list->getRoot()->getLayerMatrix()->getLength() == 4) {
      type = "RGBA";
   } else {
      std::cout << "Invalid data set, InputMatrix equals " << inputMatrixes[0]->getLength() << "\n";
      exit (0);
   }

   std::cout << "The current type of image being used is " << type;
   for (int i = 0; i < 10; i++) {
      inputImageFolder = (string) filesystem::current_path() + "/../data/images/mnist_png/training/" + std::to_string(i) + '/';
      std::cout << (i * 10.0) << " percent of the images have been loaded";
      int counter = 0;
      for (const auto & entry : filesystem::directory_iterator(inputImageFolder)) {
         std::cout << entry.path() << std::endl;
         inputMatrixes[startOfDirectoryIndex + counter] = images::generate::inputMatrixNormalized(entry.path(), type);
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
   std::cout << "The images have finished loading";

   int correct = 0;
   float total = 0;
   for (int i = 0; i < inputCount; i++) {
      list->editRootMatrix(inputMatrixes[i]);

      // std::cout << "before";
      // list->print(true, true);
      list->calculateAndUpdateAll();
      float max = 0;
      int maxIndex = 0;
      for (int k = 0; k < 10; k++) {
         if (*list->getLast()->getLayerMatrix()->getData(0, 0, k) > max) {
            maxIndex = k;
            max = *list->getLast()->getLayerMatrix()->getData(0, 0, k);
         }
      }

      int outputIndex = 0;
      for (int k = 0; k < 10; k++) {
         if (*outputMatrixes[i]->getData(0, 0, k) > 0.5) {
            outputIndex = k;
            break;
         }
      }
      if (outputIndex == maxIndex) {
         correct++;
      } 
      total++;
      list->getLast()->getLayerMatrix()->printMatrix();
      outputMatrixes[i]->printMatrix();
      std::cout << "Error = " << correct / total * 100 << "%\n\n";
   }


   // std::cout << std::setprecision(4);
   // double sumFinal = 0;
   // for (int i = 0; i < inputCount; i++) {
   //    list->editRootMatrix(inputMatrixes[i]);
   //    list->calculateAndUpdateAll();
   //    Matrix3D<float>* error = *outputMatrixes[i] - list->getLast()->getLayerMatrix();
   //    Matrix3D<float>* squared = *error * error;
   //    sumFinal += squared->sum() * 100;
   //    delete error;
   //    delete squared;
   // }
   // std::cout << "Total final error :: " << sumFinal << "%\n";


   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   std::cout << "\nMemory used (MB): " << usage.ru_maxrss / 1000000 << "\n\n";
}