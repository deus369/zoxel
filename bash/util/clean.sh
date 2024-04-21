#!/bin/bash

# clean b build files

echo " > clearing zox make"

clean_directory() {
    local directory="$1"
    if [ -d "$directory" ]; then
        echo " - cleared directory [$directory]"
        rm -r "$directory"
    else
        echo " + directory did not exist [$directory]"
    fi
}

clean_directory "build"
clean_directory "include"
clean_directory "lib"
