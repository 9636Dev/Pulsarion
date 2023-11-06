#!/bin/bash

# Function to list all executables in the bin directory recursively
list_executables() {
    local count=0
    local files=()
    
    while IFS= read -r -d $'\0' file; do
        ((count++))
        echo "$count) $file"
        files+=("$file")
    done < <(find bin -type f -perm +111 -print0)

    echo "Select the executable to run (1-$count):"
    read -r choice

    # Check if the choice is an integer and within the valid range
    if ! [[ "$choice" =~ ^[0-9]+$ ]] || ((choice < 1 || choice > count)); then
        echo "Invalid selection. Exiting."
        exit 1
    fi

    # Get the selected file
    local exec_file=${files[$((choice - 1))]}
    
    # Run the executable
    echo "Running $exec_file..."
    "$exec_file"
    
    # Capture the exit code
    local exit_code=$?
    
    echo "Executable finished with exit code: $exit_code"
}

# Check if the bin directory exists
if [ ! -d bin ]; then
    echo "The directory 'bin' does not exist."
    exit 1
fi

list_executables
