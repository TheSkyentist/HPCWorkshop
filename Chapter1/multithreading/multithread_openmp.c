// Multithreaded program to calculate the sum of the first n natural numbers using OpenMP
// Compile using gcc multithread_openmp.c -o multithread_openmp.out -fopenmp
 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Number of threads controlled by the environment variable OMP_NUM_THREADS
  
// Parallel programming function 
long long sum_parallel(int n) 
{ 
    long long sum = 0; 

// The following pragma statement tells the compiler to parallelize the for loop
#pragma omp parallel for reduction(+ : sum) 
    for (int i = 0; i <= n; ++i) { 
        sum += i;
    } 
    return sum; 
} 
  
// Main Function 
int main() 
{ 

    const int n = 100000000; 

    long long result_parallel = sum_parallel(n); 
    printf("Sum: %lld\n", result_parallel);

    return 0; 
}
