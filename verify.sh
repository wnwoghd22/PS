#!/bin/bash

# Set the executable filename
executable="./main.exe"

# Define the log file for test results
log_file="test_results.log"

# Loop through each .in file in the directory
for input_file in *.in; do
    # Check if there is a corresponding .ans file
    if [ -f "${input_file%.in}.ans" ]; then
        # Set output file name
        output_file="${input_file%.in}.out"
        
        # Get the corresponding answer file
        answer_file="${input_file%.in}.ans"

        # Print output
        "$executable" < "$input_file" > "$output_file"
        
        # Convert the output file to LF
        dos2unix "$output_file" > /dev/null 2>&1
        
        # Read the contents of the answer file
        expected_output=$(<"$answer_file")
        
        # Compare the output with the expected output
        if diff "$output_file" $"$answer_file" 1>/dev/null; then
            result="Passed"
        else
            result="Failed"
        fi
        
        # Output the test result to console and log file
        echo "Test case ${input_file%.in}: $result"
        echo "Test case ${input_file%.in}: $result" >> "$log_file"
    else
        echo "No answer file found for ${input_file%.in}"
    fi
done
