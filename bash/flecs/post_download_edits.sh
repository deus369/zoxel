#!/bin/bash

# this is for flecs version 3.2.6 only
file_path="include/flecs/flecs.c"
# this is done because flecs on windows has an error closing
line_number=5903
replacement_line="    if (entity == 0) return;"

# Check if the file exists
if [ -f "$file_path" ]; then
    # Replace the line
    sed -i "${line_number}s/.*/${replacement_line}/" "$file_path"
    echo " + flecs file modified at [$line_number] with [$replacement_line]"
else
    echo " - flecs file '$file_path' not found."
fi
