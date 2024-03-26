#! /usr/bin/env python

# Calculate squares in parallel

# Import packages
from multiprocessing import Pool

# Square number
def square(number):
    return number * number

# Calculate squares of numbers in parallel
def calculate_squares(numbers):

    # Create a pool of workers
    with Pool(processes=10) as pool:
        # Map the 'square' function to the list of numbers
        chunksize = 10 # The number of elements per chunk, very important!
        results = pool.map_async(square, numbers, chunksize)
        pool.close()
        pool.join()
    return results

# Main function
if __name__ == "__main__":

    # Define a list of numbers
    numbers = range(1_000+1) 
    squared_numbers = calculate_squares(numbers)
    print(squared_numbers[:5],'...',squared_numbers[-5:])