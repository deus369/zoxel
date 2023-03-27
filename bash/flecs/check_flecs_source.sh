#!/bin/bash

# Check if the file exists
if [ -f "include/flecs/flecs.c" ]; then
    echo "  > flecs source found"
    exit 1 # Set success status
else
    echo "  > flecs source not found"
    exit 0 # Set failure status
fi