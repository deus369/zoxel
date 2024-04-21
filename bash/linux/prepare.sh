#!/bin/bash

# first download libraries
# source bash/linux/download_libraries.sh

build_path="build/linux"
build_dev_path="build/linux-dev"
resources="resources" # todo: change to just resources
# if [ ! - d $build_path ] mkdir $build_path ;
# Function to create directory if it doesn't exist
prepare_build_directory() {
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
    # no need for dlls with linux builds, just need system installed sdl2/glew
    # will this work tho if not?
    #mkdir "$build_bin"
    #cp build/sdl/lib/x64/SDL2.dll $build_bin/SDL2.dll
    #cp build/sdl_image/lib/x64/SDL2_image.dll $build_bin/SDL2_image.dll
    #cp build/sdl_mixer/lib/x64/SDL2_mixer.dll $build_bin/SDL2_mixer.dll
    #cp build/glew/bin/Release/x64/glew32.dll $build_bin/glew32.dll
    # do this for now, can't get exe to recognize dlls
    #cp -r $build_bin/* $directory/
}
prepare_build_directory "$build_path"
prepare_build_directory "$build_dev_path"
