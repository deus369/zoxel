#!/bin/bash

lib_check_filepath="lib/libflecs.a"
# Check if the file exists
if [ -f $lib_check_filepath ]; then
    echo "  > found [$lib_check_filepath] proceeding.."
    exit 0 # Set success status
else
    echo "  - [$lib_check_filepath] does not exist"
    echo "#####"
    echo "  > remember to build flecs lib with 'make build/libflecs.a'"
    echo "#####"
    exit 1 # Set failure status
fi