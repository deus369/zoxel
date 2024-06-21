#!/bin/bash

source bash/util/prepare_directories.sh

# first download libraries
source bash/windows/download_libraries.sh

source bash/freetype/install.sh

build_path="build/windows"
build_dev_path="build/windows-dev"
resources="resources" # todo: change to just resources
lib="lib"
windows_threads_dll="bash/windows/libwinpthread-1.dll"
if [ ! -f $lib/libwinpthread-1.dll ]; then
    echo " + copying []$windows_threads_dll] to [$lib/libwinpthread-1.dll]"
    cp $windows_threads_dll $lib/libwinpthread-1.dll
else
    echo " > [$lib/libwinpthread-1.dll] already exists"
fi
# if [ ! - d $build_path ] mkdir $build_path ;
# Function to create directory if it doesn't exist
prepare_build_directory() {
    local directory="$1"
    local build_resources="$directory/resources"
    local directory_lib="$directory/lib"
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
    if [ -d "$directory_lib" ]; then
        echo " + removing old lib [$directory_lib]"
        rm -rf "$directory_lib"
    else
        echo " > old bin [$directory_lib] did not exist"
    fi
    mkdir "$directory_lib"
    echo " + copying dlls from lib to [$directory_lib]"
    cp -r $lib/*.dll $directory_lib/
    # do this for now, can't get exe to recognize dlls
    echo " + copying dlls out of lib to build directory [$directory_lib]"
    cp -r $directory_lib/*.dll $directory/
}
prepare_build_directory "$build_path"
prepare_build_directory "$build_dev_path"
