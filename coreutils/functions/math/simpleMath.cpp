#ifndef SIMPLE_MATH
#define SIMPLE_MATH

#include <cmath>
#include <random>
// #include <coreutils/functions/sort/sortHelpers.cpp>
// #include <coreutils/functions/debug/print.cpp>

namespace coreutils 
{
   namespace functions
   {
      namespace math {
         // determines if value is prime
         bool isPrime (int prime);

         // random number between beginning and end
         double rand (int beginning, int end);

         // determines if value is a palindrome (only works with ints)
         bool isPalindrome (int p);

         // counts the number of digits in a number
         int countDigits (int n);

         bool isPrime (int prime) {
            for (int i = sqrt (prime); i > 1; i--) {
               if (prime % i == 0) {
                  return false;
               }
            }

            return true;
         }

         double rand (int beginning, int end) {
            if (beginning > end) {
               std::cout << "Invalid input into rand\n";
               return -1;
            }
            std::mt19937_64 rng;
            uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
            rng.seed(ss);
            std::uniform_real_distribution<double> unif(0, 1);

            return unif(rng) * (end - beginning) + beginning;
         }

         bool isPalindrome (int p) {
            for (float i = 6; i > 0; i--){
               if (p % (int) pow (10.0, i) != 0){
                  for (float j = i - 1; j > 0; j--){
                     if (p / (int) pow (10.0, j) % 10 != p % (int) pow (10.0, i - j) / (int) pow (10.0, i - j - 1)){
                        return false;
                     } 
                  }

                  // exit (0);
                  return true;
               }
            }
            return false;
         }

         int countDigits (int n)
         {
            int count = 0;
            while (n != 0)
            {
               n = n / 10;
               ++count;
            }
            return count;
         }
      }
   }
}
#endif