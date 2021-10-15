#ifndef ACTIVATION_FUNCTIONS
#define ACTIVATION_FUNCTIONS

#include <cmath>

namespace artificialIntelligence {
   namespace functions {
      namespace activation {

      // sigmoid function
         double sigmoid (double x);

         // derivative of the sigmoid function
         double dSigmoid (double x);

         double sigmoid(double x) 
         { 
            return 1 / (1 + exp(-x)); 
         }
         double dSigmoid(double x) 
         { 
            return x * (1 - x);
         }
      }
   }
}


#endif

