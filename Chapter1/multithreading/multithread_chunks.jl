#! /usr/bin/env julia

# Description: Multithreading in Julia
# Run as `julia multithread_chunks.jl`
# Export the number of threads with the environment variable JULIA_NUM_THREADS

# Load the required package
using Base.Threads

# Function to calculate the sum of integers from 1 to n in parallel
function sum_parallel_chunks(n::Int)
    num_threads = nthreads()
    chunk_sums = zeros(Int64, num_threads)
    chunk_size = ceil(Int, n / num_threads)

    @threads for t in 1:num_threads
        start_idx = (t-1) * chunk_size + 1
        end_idx = min(t * chunk_size, n)
        for i = start_idx:end_idx
            chunk_sums[t] += i
        end
    end

    return sum(chunk_sums)
end

const n = 100_000_000
result_parallel = @time sum_parallel_chunks(n)
println("Sum: ", result_parallel)