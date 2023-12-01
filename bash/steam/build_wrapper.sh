#!/bin/sh
# builds test_steamworks

wrapper_cpp="bash/steam/steamwrapper.cpp"
lib_output="lib/libsteam_wrapper.so"

if [ ! -d lib ]; then
    mkdir lib
fi

# builds library
#builds test_steamworks
echo " > building steam-wrapper [$lib_output]"
g++ -shared $wrapper_cpp -o $lib_output -Iinclude/steam -Llib -lsteam_api -fPIC

# todo: move wrapper copying into make build step
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

echo " > copying libsteam_api.so into build/linux"
cp lib/libsteam_api.so build/linux/lib/libsteam_api.so

echo " > copying [$lib_output] into build/linux"
cp $lib_output build/linux/lib/libsteam_wrapper.so
