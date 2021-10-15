#ifndef STRING_FUNCTIONS
#define STRING_FUNCTIONS

#include <string>

namespace coreutils {
   namespace functions {
      namespace procedural {

         // splits the string on the delimeter and returns as array and returns size
         std::vector<std::string>* split (std::string input, std::string delimeter, int* size);

         // splits the string on the delimeter and returns as array and returns size
         std::vector<std::string>* split (std::string input, std::string delimeter, int* size);

         std::vector<std::string>* split (std::string input, std::string delimeter) {
            std::vector<std::string>* returnValue = new std::vector<std::string> ();
            int index = input.find (delimeter);
            while (index != std::string::npos) {
               returnValue->push_back (input.substr(0, index));
               input = input.substr (index + 1);
               index = input.find (delimeter);
            }
            returnValue->push_back (input);
            return returnValue;
         }

         std::vector<std::string>* split (std::string input, std::string delimeter, int* size) {
            std::vector<std::string>* returnValue = new std::vector<std::string> ();
            int index = input.find (delimeter);
            while (index != std::string::npos) {
               returnValue->push_back (input.substr(0, index));
               (*size)++;
               input = input.substr (index + 1);
               index = input.find (delimeter);
            }
            returnValue->push_back (input);
            (*size)++;
            return returnValue;
         }
      }
   }
}




#endif