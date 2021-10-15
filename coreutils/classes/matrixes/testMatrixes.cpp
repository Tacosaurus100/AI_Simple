#include <iostream>
#include <coreutils/classes/matrixes/Matrix3D.cpp>

using namespace coreutils::classes::matrixes;

int main () {
   coreutils::classes::matrixes::Matrix;
   Matrix3D<double>* M3D = new Matrix3D<double> (2, 2, 2);
   Matrix3D<double>* M3D2 = new Matrix3D<double> (2, 2, 2);
   M3D->randomize();
   M3D->printMatrix();
   std::cout << '\n';
   M3D2->randomize();
   M3D2->printMatrix();
   Matrix3D<double>* M3DAdd = *M3D + *M3D2;
   M3DAdd->printMatrix();
   std::cout << M3D->dotProduct(M3D2);
}