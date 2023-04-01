#!/bin/bash

lib_check_filepath="lib/libflecs.a"
# Check if the file exists
if [ -f $lib_check_filepath ]; then
    echo "  > found [$lib_check_filepath]"
    exit 1 # Set success status
else
    echo "  > not found [$lib_check_filepath]"
    exit 0 # Set failure status
fi