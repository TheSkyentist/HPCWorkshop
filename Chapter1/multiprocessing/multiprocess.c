// Square array elements using 2 processes with fork() and shared memory
// Compile with gcc multiprocess.c -o multiprocess.out

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 1000  // Size of the array

void square_numbers(int *arr, int start, int end) {
    for (int i = start; i < end; i++) {
        arr[i] = arr[i] * arr[i];
    }
}

int main() {
    int segment_id = shmget(IPC_PRIVATE, SIZE * sizeof(int), IPC_CREAT | 0666);
    int *shared_array = (int *)shmat(segment_id, NULL, 0);

    // Initialize array
    for (int i = 0; i < SIZE; i++) {
        shared_array[i] = i + 1;  // Fill with numbers 1 to SIZE
    }

    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid == 0) {  // Child process
        square_numbers(shared_array, 0, SIZE / 2);
        shmdt(shared_array);
        exit(0);
    } else {  // Parent process
        square_numbers(shared_array, SIZE / 2, SIZE);
        wait(NULL);  // Wait for child process to finish
        // Print squared numbers
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", shared_array[i]);
        }
        printf("\n");
        shmdt(shared_array);
        shmctl(segment_id, IPC_RMID, NULL);  // Clean up shared memory
    }
    return 0;
}
