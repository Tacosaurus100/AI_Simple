#ifndef IMAGES_GENERATE_CPP
#define IMAGES_GENERATE_CPP

#include <Magick++.h> 

#include <artificialIntelligence/functions/images/generateInput.hpp>
#include <coreutils/classes/matrixes/Matrix3D.cpp>

using namespace Magick;
using namespace coreutils::classes::matrixes;

namespace artificialIntelligence {
   namespace functions {
      namespace images {
         namespace generate {
            template <typename T>
            void inputMatrixNormalized (std::string filepath, Matrix3D<T>* m3d, std::string type) {
               Image image(filepath);
               Geometry dimensions = image.size();
         
               if (type == "BW") {
                  m3d = new Matrix3D<T>(1, dimensions.width(), dimensions.height());
               }
               else if (type == "RGB") {
                  m3d = new Matrix3D<T>(3, dimensions.width(), dimensions.height());
               }
               else {
                  m3d = new Matrix3D<T>(4, dimensions.width(), dimensions.height());
               }
               for (int i = 0; i < dimensions.width(); i++) {
                  for (int j = 0; j < dimensions.height(); j++) {
                     Color c = image.pixelColor( i, j );
                     float r = c.quantumRed() / QuantumRange;
                     float g = c.quantumGreen() / QuantumRange;
                     float b = c.quantumBlue() / QuantumRange;
                     float a = c.quantumAlpha() / QuantumRange;
                     m3d->insert(r, 0, i, j);
                     if (type != "BW") {
                        m3d->insert(g, 1, i, j);
                        m3d->insert(b, 2, i, j);
                        if (type != "RGB") {
                           m3d->insert(a, 3, i, j);
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

#endif