#!/bin/bash

# Define variables
opengl_git_url="https://gitlab.freedesktop.org/mesa/mesa.git"
# "https://github.com/KhronosGroup/OpenGL-Registry.git"
opengl_install_directory="build/opengl"

if [ -d $opengl_install_directory ]; then
    echo "  > directory exists [$opengl_install_directory]"
else
    #  -b release-2.26.x
    echo "  > directory does not exist [$opengl_install_directory]"
    git clone $opengl_git_url $opengl_install_directory
    rm -rf $opengl_install_directory/.git
fi

cd $opengl_install_directory/.git
# ./configure
# make
mkdir build
cd build
meson ..
# sudo ninja install
cd ../../..
