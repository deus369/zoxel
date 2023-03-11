#!/bin/bash

# Check if the file exists
if [ -f "build/libflecs.a" ]; then
    echo "  > [build/libflecs.a] exists, proceeding with build"
    exit 0 # Set success status
else
    echo "  - [build/libflecs.a] does not exist."
    echo "#####"
    echo "Remember to build flecs lib with 'make build/libflecs.a'"
    echo "#####"
    exit 1 # Set failure status
fi