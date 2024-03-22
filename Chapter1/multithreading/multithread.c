// Multithreaded program to calculate the sum of the first n natural numbers
// Compile using gcc multithread.c -o multithread.out -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 10

typedef struct {
    int start;
    int end;
    long long sum;
} ThreadData;

// Thread function to calculate part of the sum
void* partial_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->sum = 0; // Initialize sum for this segment

    for (int i = data->start; i <= data->end; ++i) {
        data->sum += i;
    }

    pthread_exit(NULL);
}

// Function to calculate sum in parallel
long long sum_parallel(int n) {
    pthread_t threads[THREAD_COUNT];
    ThreadData threadData[THREAD_COUNT];
    int segmentSize = n / THREAD_COUNT;
    long long totalSum = 0;

    // Create threads to calculate partial sums
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threadData[i].start = i * segmentSize + 1;
        if (i == THREAD_COUNT - 1) {
            threadData[i].end = n; // Last thread covers any remaining elements
        } else {
            threadData[i].end = (i + 1) * segmentSize;
        }
        
        if (pthread_create(&threads[i], NULL, partial_sum, &threadData[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Join threads and accumulate their results
    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(threads[i], NULL);
        totalSum += threadData[i].sum;
    }

    return totalSum;
}

int main() {
    const int n = 100000000;
    long long result_parallel = sum_parallel(n);
    printf("Sum: %lld\n", result_parallel);

    return 0;
}