#ifndef BASIC_WEIGHT_HPP
#define BASIC_WEIGHT_HPP

#include <iostream>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

using namespace coreutils::classes::matrixes;

namespace artificialIntelligence {
   namespace classes {

      template <typename T>
      class BasicWeight {
         public:
            //
            BasicWeight (Matrix3D<T>* weights);
            
            BasicWeight (int fl, int fw, int fh, int sl, int sw, int sh);

            BasicWeight ();

            void print ();

            BasicWeight<T>* add (int length, int width, int height, Matrix3D<T>* weights = nullptr);

            BasicWeight<T>* addNew (int length, int width, int height);

            Matrix3D<T>* getWeightMatrix (int length, int width, int height);

            Matrix3D<T>* getWeightMatrix ();

         private:

            // Cube where start is at the front top left corner.

            Matrix3D<T>* weights;

            // corresponds to length
            BasicWeight<T>* right;

            // corresponds to width;
            BasicWeight<T>* back;

            // corresponds to height
            BasicWeight<T>* down;

            // prints the matrixes in a reasonable manner with a count of them
            int print (int length, int width, int height);

            // generates nodes along the entire rectangular prism of side lengths from parameters
            void generate (int fl, int fw, int fh, int sl, int sw, int sh);
      };
   }
}


#endif