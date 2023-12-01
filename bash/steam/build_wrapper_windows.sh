#!/bin/sh
# builds test_steamworks

wrapper_cpp="bash/steam/steamwrapper.cpp"
lib_output="lib/libsteam_wrapper.dll"

# builds library
#builds test_steamworks
echo " > building steam-wrapper [$lib_output]"
x86_64-w64-mingw32-g++ -shared $wrapper_cpp -o $lib_output -Iinclude/steam -Llib -lsteam_api64 -fPIC

# todo: move wrapper copying into make build step
if [ ! -d build ]; then
    echo " > creating build directory"
    mkdir build
fi
if [ ! -d build/windows ]; then
    echo " > creating build/windows directory"
    mkdir build/windows
fi
if [ ! -d build/windows/lib ]; then
    echo " > creating build/windows/lib directory"
    mkdir build/windows/lib
fi
echo " > copying steam_api64.dll into build/windows"
cp lib/steam_api64.dll build/windows/lib/steam_api64.dll
echo " > copying [$lib_output] into build/windows"
cp $lib_output build/windows/lib/libsteam_wrapper.dll
