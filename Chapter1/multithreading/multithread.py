#! /usr/bin/env python

# Import packages
from concurrent.futures import ThreadPoolExecutor

# Define the total number of numbers and number of threads
SIZE = 1000000
THREAD_COUNT = 10

# Define the function to sum a range of numbers
def sum_range(start, end):
    """Sum a range of numbers from start to end (inclusive)."""
    return sum(range(start, end+1))

# Create a thread pool and submit tasks to sum the numbers
with ThreadPoolExecutor(max_workers=THREAD_COUNT) as executor:
    segment_size = SIZE // THREAD_COUNT
    # Adjust the ranges for each task to cover all numbers from 1 to SIZE
    futures = [executor.submit(sum_range, i * segment_size + 1, (i + 1) * segment_size if i < THREAD_COUNT - 1 else SIZE) for i in range(THREAD_COUNT)]
    partial_sums = [future.result() for future in futures]

total_sum = sum(partial_sums)
print(f"Sum: {total_sum}")