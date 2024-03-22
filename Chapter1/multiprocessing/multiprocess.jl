#! /usr/bin/env julia

using Distributed

# Add processes (if not started with `julia -p n`)
addprocs(10) 
# addprocs([("localhost", 2), ("astro-node10", 2)], topology=:master_worker)

# Define a function to square a number
@everywhere function square(number)
    return number * number
end

# Example function to precompile 'square'
@everywhere begin
    square(1)
end

# Define a range of numbers
numbers = 0:1_000 # Define the range of numbers

# Define a function to calculate squares
function calculate_squares(numbers)
    return pmap(square, numbers)
end

# Timing the execution
@time squared_numbers = calculate_squares(numbers)

println(squared_numbers[1:5],"...",squared_numbers[end-4:end])