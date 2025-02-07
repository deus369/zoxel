#!/bin/bash

game="$1"
if [ $game -eq "" ]; then
    echo "No Game Found"
    return 0
fi

bash bash/util/prepare_directories.sh

echo " + creating game build folder [$game-linux]"
build_path="build/$game-linux"
resources="resources"
lib="lib"
# if [ ! - d $build_path ] mkdir $build_path ;
# Function to create directory if it doesn't exist
prepare_linux_build_directory() {
    local directory="$1"
    local build_resources="$directory/resources"
    local directory_lib="$directory/lib"
    # local build_bin="$directory/bin"
    if [ ! -d "$directory" ]; then
        mkdir -p "$directory"
        echo " + created new build directory [$directory]"
    else
        echo " > directory [$directory] already exists"
    fi
    # resources
    if [ -d "$build_resources" ]; then
        echo " + removing old resources [$build_resources]"
        rm -rf "$build_resources"
    else
        echo " > [$build_resources] did not exist"
    fi
    mkdir "$build_resources"
    cp -r $resources/* $build_resources/
    # now copy bin files in
    #if [ -d "$build_bin" ]; then
    #    echo " + removing old bin [$build_bin]"
    #    rm -rf "$build_bin"
    #else
    #    echo " > old bin [$build_bin] did not exist"
    #fi
    if [ ! -d "$directory_lib" ]; then
        mkdir -p "$directory_lib"
        echo " + created new build directory lib [$directory_lib]"
    else
        echo " > directory [$directory_lib] already exists"
    fi
    cp -r $lib/*.so $directory_lib/
    cp -r $lib/*.so.0 $directory_lib/
    cp -r $lib/*.a $directory_lib/
}

prepare_linux_build_directory "$build_path"