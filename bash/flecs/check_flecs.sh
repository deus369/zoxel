#!/bin/bash

# Check if the file exists
if [ -f "include/flecs/flecs.c" ]; then
    echo "Flecs code found in include directory."
    exit 1 # Set success status
else
    echo "Flecs code not found. Downloading Flecs 3.1.3."
    exit 0 # Set failure status
fi