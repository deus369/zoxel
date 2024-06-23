#!/bin/bash

# this is for flecs version 3.2.6 only
file_path="include/flecs/flecs.c"
# this is done because flecs on windows has an error closing
line_number=5903
replacement_line="    if (entity == 0) return;"

# Check if the file exists
if [ -f "$file_path" ]; then
    # Replace the line
    echo " - disabled this edit for now"
    #sed -i "${line_number}s/.*/${replacement_line}/" "$file_path"
    #echo " + flecs file modified at [$line_number] with [$replacement_line]"
else
    echo " - flecs file '$file_path' not found."
fi

# this is done because flecs on web has issues
line_number_2=6095
replacement_line_2="    if (!ecs_is_alive(world, entity)) return NULL;"

# Check if the file exists
if [ -f "$file_path" ]; then
    # Replace the line
    echo " - disabled this edit for now"
    # sed -i "${line_number_2}s/.*/${replacement_line_2}/" "$file_path"
    # echo " + flecs file modified at [$line_number_2] with [$replacement_line_2]"
else
    echo " - flecs file '$file_path' not found."
fi
