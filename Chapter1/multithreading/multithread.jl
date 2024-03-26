#! /usr/bin/env julia

# Description: Multithreading in Julia
# Run as `julia multithread.jl`
# Export the number of threads with the environment variable JULIA_NUM_THREADS

# Load the required package
using Base.Threads

# Function to calculate the sum of integers from 1 to n in parallel
function sum_parallel(n::Int)
    sum = Atomic{Int64}(0) # Thread safe
    @threads for i in 1:n
        atomic_add!(sum, i) # Thread safe
    end
    return sum[]
end

# Main program
const n = 1_000_000
result_parallel = @time sum_parallel(n)
println("Sum: ", result_parallel)
