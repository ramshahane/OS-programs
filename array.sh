#!/bin/bash

# Function to check if a number is prime
is_prime() {
    local num=$1
    if (( num <= 1 )); then
        return 1
    fi
    for (( i=2; i*i<=num; i++ )); do
        if (( num % i == 0 )); then
            return 1
        fi
    done
    return 0
}

# Read 25 numbers into an array
numbers=()
echo "Enter 25 numbers:"
for (( i=0; i<25; i++ )); do
    read -p "Enter number $(($i+1)): " num
    numbers+=($num)
done

# Initialize arrays for prime, even, and odd numbers
prime_numbers=()
even_numbers=()
odd_numbers=()

# Process each number
for num in "${numbers[@]}"; do
    case $num in
        # Prime check
        *)
            is_prime $num
            if [ $? -eq 0 ]; then
                prime_numbers+=($num)
            fi
            ;;
    esac

    case $(( num % 2 )) in
        0)
            even_numbers+=($num)
            ;;
        1)
            odd_numbers+=($num)
            ;;
    esac
done

# Display the results
echo "Prime numbers: ${prime_numbers[@]}"
echo "Even numbers: ${even_numbers[@]}"
echo "Odd numbers: ${odd_numbers[@]}"
