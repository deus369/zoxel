#!/bin/bash

create_simple_directory() {
    local directory="$1"
    if [ ! -d "$directory" ]; then
        mkdir -p "$directory"
        echo " + created new directory [$directory]"
    else
        echo " > directory exists [$directory]"
    fi
}

create_simple_directory "build"
create_simple_directory "include"
create_simple_directory "lib"
