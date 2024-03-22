// Square array elements using MPI
// Compile with mpicc multiprocess_mpi.c -o multiprocess_mpi.out
// Run with mpiexec -np 10 ./multiprocess_mpi.out

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int main(int argc, char *argv[]) {
    int world_size, world_rank;

    // Initialize MPI
    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the process

    // Divide the array in equal-sized chunks
    int segment_size = SIZE / world_size;
    int *numbers = NULL;
    int local_numbers[segment_size];

    // The root process initializes the full array
    if (world_rank == 0) {
        numbers = malloc(SIZE * sizeof(int));
        for (int i = 0; i < SIZE; i++) {
            numbers[i] = i + 1;  // Fill with numbers 1 to SIZE
        }
    }

    // Scatter the numbers to all processes
    MPI_Scatter(numbers, segment_size, MPI_INT, local_numbers, segment_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process squares its segment of the array
    for (int i = 0; i < segment_size; i++) {
        local_numbers[i] = local_numbers[i] * local_numbers[i];
    }

    // Gather the squared numbers back to the root process
    MPI_Gather(local_numbers, segment_size, MPI_INT, numbers, segment_size, MPI_INT, 0, MPI_COMM_WORLD);

    // The root process prints the results
    if (world_rank == 0) {
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        free(numbers);
    }

    MPI_Finalize();
    return 0;
}