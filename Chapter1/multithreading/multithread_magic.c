// Compute the sum of the first n natural numbers
// Compile using gcc multithread_magic.c -o multithread_magic.out

#include <stdio.h>
#include <stdlib.h>
  
// Main Function 
int main() 
{ 
    const long n = 1000000; 

    long long result = n*(n+1)/2;
    printf("Sum: %lld\n", result);

    return 0; 
}
