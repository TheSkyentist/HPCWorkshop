#! /usr/bin/env python
# Run with 4 processes: mpiexec -n 4 python multiprocess_mpi.py

# Import packages
from mpi4py import MPI

# Initialize MPI
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

# Define function to square numbers
def square_array(arr):
    return [a*a for a in arr]

# Main function
def main():
    # Root process generates data
    if rank == 0:
        data_size = 1_000  # Size of the array
        data = list(range(data_size+1)) # Generate array of numbers
        data = [data[::i+1] for i in range(size)] # Distribute to processes
    else:
        data = None

    # Chunk data

    # Scatter data to all processes
    data = comm.scatter(data, root=0)

    # Each process squares its part of the data
    result = square_array(data)

    # Gather results from all processes
    gathered_result = comm.gather(result, root=0)

    # Print results from root process
    if rank == 0:
        print("Squared data:", gathered_result[0][:10],'...',gathered_result[-1][-10:])

if __name__ == "__main__":
    main()