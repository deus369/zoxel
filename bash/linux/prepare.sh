#!/bin/bash

# first install required packages
source bash/util/install_required.sh

# next fix up directories
source bash/util/prepare_directories.sh

# first download libraries
source bash/linux/download_libraries.sh

build_path="build/linux"
build_dev_path="build/linux-dev"
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
    cp -r $lib/*.a $directory_lib/
    cp -r $lib/*.la $directory_lib/
    cp -r $lib/*.so $directory_lib/
}

prepare_linux_build_directory "$build_path"
prepare_linux_build_directory "$build_dev_path"
