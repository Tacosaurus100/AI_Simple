#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>

#include <coreutils/functions/Matrix3D.cpp>

namespace artificialIntelligence {
   namespace cuda {
      namespace testing {

         #define N (2048*2048)
         #define THREADS_PER_BLOCK 512

         static void testCuda() {
            std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
            std::cout << std::fixed;
            std::cout << std::setprecision(4);
            double j = 1;
            for (int i = 0; i < 1000 * 1000 * 1000; i++) { 
               j += 1;
            }
            std::chrono::duration<double> final = std::chrono::steady_clock::now() - startTime;
            std::cout.precision(9);
            std::cout << "\nTime to Complete: " << std::fixed << final.count() << "s\n";
            struct rusage usage;
            getrusage (RUSAGE_SELF, &usage);
            std::cout << "\nMemory used (MB): " << usage.ru_maxrss / 1000000 << "\n\n";
         }

         int main(void) {
            int *a, *b, *c; // host copies of a, b, c
            int *d_a, *d_b, *d_c; // device copies of a, b, c
            int size = N * sizeof(int);
            // Alloc space for device copies of a, b, c
            cudaMalloc((void **)&d_a, size);
            cudaMalloc((void **)&d_b, size);
            cudaMalloc((void **)&d_c, size);
            // Alloc space for host copies of a, b, c and setup input values
            a = (int *)malloc(size); random_ints(a, N);
            b = (int *)malloc(size); random_ints(b, N);
            c = (int *)malloc(size);

            // Copy inputs to device
            cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
            cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
            // Launch add() kernel on GPU
            add<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_a, d_b, d_c);
            // Copy result back to host
            cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
            // Cleanup
            free(a); free(b); free(c);
            cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
            return 0;
         }
      }
   }
}