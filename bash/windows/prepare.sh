#!/bin/bash
lib="lib"
resources="resources"
build_path="build/windows"
build_dev_path="build/windows-dev"

bash bash/util/prepare_directories.sh
bash bash/freetype/install.sh
bash bash/windows/install_winpthread.sh
# source bash/windows/download_libraries.sh
if yay -Q mingw-w64-glew > /dev/null 2>&1; then
    echo " > mingw-w64-glew is installed"
else
    echo " + mingw-w64-glew is not installed"
    yay -S --noconfirm mingw-w64-glew
fi
# bash bash/glew/install.sh build/glew "dll"
bash bash/sdl/install_sdl.sh build/sdl "dll"
# yay -S --noconfirm mingw-w64-SDL2_image
# yay -S --noconfirm mingw-w64-SDL2_mixer
bash bash/sdl/install_sdl_image.sh build/sdl_image "dll"
bash bash/sdl/install_sdl_mixer.sh build/sdl_mixer "dll"

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
