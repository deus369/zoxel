#!/bin/bash

source bash/util/prepare_directories.sh

# first download libraries
# source bash/linux/download_libraries.sh

build_path="build/linux"
build_dev_path="build/linux-dev"
resources="resources"
# if [ ! - d $build_path ] mkdir $build_path ;
# Function to create directory if it doesn't exist
prepare_linux_build_directory() {
    local directory="$1"
    local build_resources="$directory/resources"
    local build_bin="$directory/bin"
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
    if [ -d "$build_bin" ]; then
        echo " + removing old bin [$build_bin]"
        rm -rf "$build_bin"
    else
        echo " > old bin [$build_bin] did not exist"
    fi
}

prepare_linux_build_directory "$build_path"
prepare_linux_build_directory "$build_dev_path"
