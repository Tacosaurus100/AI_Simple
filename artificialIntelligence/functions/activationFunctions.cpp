#ifndef ACTIVATION_FUNCTIONS
#define ACTIVATION_FUNCTIONS

#include <cmath>
#include <coreutils/classes/matrixes/Matrix3D.cpp>
#include <artificialIntelligence/functions/activationFunctions.hpp>

using namespace coreutils::classes::matrixes;

namespace artificialIntelligence {
   namespace functions {
      namespace activation {

         double sigmoid(double x) 
         { 
            return 1 / (1 + exp(-x)); 
         }

         double dSigmoid(double x) 
         { 
            return sigmoid(x) * (1 - sigmoid(x));
         }
         
         template <typename T>
         Matrix3D<T>* sigmoid(Matrix3D<T>* m3d) 
         { 
            Matrix3D<T>* returnMatrix = new Matrix3D<T> (m3d->getLength(), m3d->getWidth(), m3d->getHeight());
            for (int l = 0; l < m3d->getLength(); l++) {
               for (int w = 0; w < m3d->getWidth(); w++) {
                  for (int h = 0; h < m3d->getHeight(); h++) {
                     returnMatrix->insert(sigmoid (*m3d->getData(l, w, h)), l, w, h);
                  }
               }
            }
            return returnMatrix;
         }

         template <typename T>
         Matrix3D<T>* dSigmoid(Matrix3D<T>* m3d) 
         { 
            Matrix3D<T>* returnMatrix = new Matrix3D<T> (m3d->getLength(), m3d->getWidth(), m3d->getHeight());
            for (int l = 0; l < m3d->getLength(); l++) {
               for (int w = 0; w < m3d->getWidth(); w++) {
                  for (int h = 0; h < m3d->getHeight(); h++) {
                     returnMatrix->insert(dSigmoid (*m3d->getData(l, w, h)), l, w, h);
                  }
               }
            }
            return returnMatrix;
         }

         double tanh (double x) {
            return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
         }

         double dTanh (double x) {
            return pow(tanh(x), 2);
         }

         template <typename T>
         Matrix3D<T>* tanh(Matrix3D<T>* m3d) 
         { 
            Matrix3D<T>* returnMatrix = new Matrix3D<T> (m3d->getLength(), m3d->getWidth(), m3d->getHeight());
            for (int l = 0; l < m3d->getLength(); l++) {
               for (int w = 0; w < m3d->getWidth(); w++) {
                  for (int h = 0; h < m3d->getHeight(); h++) {
                     returnMatrix->insert(tanh (*m3d->getData(l, w, h)), l, w, h);
                  }
               }
            }
            return returnMatrix;
         }

         template <typename T>
         Matrix3D<T>* dTanh(Matrix3D<T>* m3d) 
         { 
            Matrix3D<T>* returnMatrix = new Matrix3D<T> (m3d->getLength(), m3d->getWidth(), m3d->getHeight());
            for (int l = 0; l < m3d->getLength(); l++) {
               for (int w = 0; w < m3d->getWidth(); w++) {
                  for (int h = 0; h < m3d->getHeight(); h++) {
                     returnMatrix->insert(dTanh (*m3d->getData(l, w, h)), l, w, h);
                  }
               }
            }
            return returnMatrix;
         }
      }
   }
}


#endif

