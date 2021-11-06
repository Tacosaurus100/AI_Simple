#include <artificialIntelligence/functions/images/generateInput.cpp>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <sys/time.h>
#include <sys/resource.h>

using namespace std;
using namespace artificialIntelligence::functions;
using namespace coreutils::classes::matrixes;

int main () {
   std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();

   string* currentPath = new string (filesystem::current_path());
   *currentPath += "/../../artificialIntelligence/neuralNetworks";
   filesystem::current_path(filesystem::path(*currentPath));

   string inputData = filesystem::current_path();
   delete currentPath;
   
   inputData += "/../data/xor/xorInputData.txt";

   Matrix3D<float>* convImage = images::generate::inputMatrix("filepath");

   std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
   std::cout.precision(9);
   std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   std::cout << "\nMemory used (MB): " << usage.ru_maxrss / 1000000 << "\n\n";
}