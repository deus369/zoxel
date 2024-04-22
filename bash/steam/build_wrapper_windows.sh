#!/bin/sh
# builds test_steamworks

steam_headers_dir=include/steam
steam_api_lib=lib/steam_api64.dll
build_dir_windows=build/windows
wrapper_cpp=bash/steam/steamwrapper.cpp
steam_wrapper_lib=lib/libsteam_wrapper.dll

# builds library
echo " > building steam-wrapper [$steam_wrapper_lib]"
x86_64-w64-mingw32-g++ -shared $wrapper_cpp -o $steam_wrapper_lib -I$steam_headers_dir -Llib -lsteam_api64 -fPIC

# moves wrapper copying into make build step
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

echo " > copying [$steam_wrapper_lib] into [$build_dir_windows]"
cp $steam_wrapper_lib $build_dir_windows/$steam_wrapper_lib

echo " > copying [$steam_api_lib] into [$build_dir_windows]"
cp $steam_api_lib $build_dir_windows/$steam_api_lib
