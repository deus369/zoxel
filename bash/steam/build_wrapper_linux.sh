#!/bin/sh
# builds test_steamworks

steam_headers_dir=include/steam
steam_api_lib=lib/libsteam_api.so
linux_build_dir=build/linux
wrapper_cpp=bash/steam/steamwrapper.cpp
steam_wrapper_lib=lib/libsteam_wrapper.so

if [ ! -d lib ]; then
    mkdir lib
fi

# builds library
#builds test_steamworks
echo " > building steam-wrapper [$steam_wrapper_lib] from [$wrapper_cpp]"
g++ -shared $wrapper_cpp -o $steam_wrapper_lib -I$steam_headers_dir -Llib -lsteam_api -fPIC

# todo: move wrapper copying into make build step
# this checks directories are created
if [ ! -d build ]; then
    echo " > creating build directory"
    mkdir build
fi
if [ ! -d build/linux ]; then
    echo " > creating build/linux directory"
    mkdir build/linux
fi
if [ ! -d build/linux/lib ]; then
    echo " > creating build/linux/lib directory"
    mkdir build/linux/lib
fi

echo " > copying [$steam_wrapper_lib] into [$linux_build_dir]"
cp $steam_wrapper_lib $linux_build_dir/$steam_wrapper_lib

echo " > copying [$steam_api_lib] into [$linux_build_dir]"
cp $steam_api_lib $linux_build_dir/$steam_api_lib
