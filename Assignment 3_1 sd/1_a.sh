#!/bin/zsh

# Check if the user provided a file name as an argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file-name>"
    exit 1
fi

file_type=$(file -b "$1")

# Get file permissions
permissions=$(ls -l "$1" | awk '{print $1}')

# Print the file type and permissions
echo "File Type: $file_type"
echo "Permissions: $permissions"
