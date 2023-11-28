#!/bin/sh
# builds test_steamworks

wrapper_cpp="bash/steam/steamwrapper.cpp"
lib_output="lib/libsteam_wrapper.dll"

# builds library
#builds test_steamworks
echo " > building steam-wrapper [$lib_output]"
x86_64-w64-mingw32-g++ -shared $wrapper_cpp -o $lib_output -Iinclude/steam -Llib -lsteam_api64 -fPIC
