#!/bin/sh

# sdk
steam_api_lib=lib/libsteam_api.so
steam_headers_dir=include/steam
# builds
build_dir_linux_steam=build/linux-steam
build_dir_windows_steam=build/windows-steam
steam_wrapper_lib=lib/libsteam_wrapper.so
steam_wrapper_lib_windows=lib/libsteam_wrapper.dll

if [ -d $build_dir_linux_steam ]; then
    echo " > cleaning build [$build_dir_linux_steam]"
    rm -R $build_dir_linux_steam
else
    echo " > build dir did not exist [$build_dir_linux_steam]"
fi

if [ -d $build_dir_windows_steam ]; then
    echo " > cleaning build [$build_dir_windows_steam]"
    rm -R $build_dir_windows_steam
else
    echo " > build dir did not exist [$build_dir_windows_steam]"
fi

if [ -f $steam_wrapper_lib ]; then
    echo " > cleaning file [$steam_wrapper_lib]"
    rm $steam_wrapper_lib
else
    echo " > build file did not exist [$steam_wrapper_lib]"
fi


if [ -f $steam_wrapper_lib_windows ]; then
    echo " > cleaning file [$steam_wrapper_lib_windows]"
    rm $steam_wrapper_lib_windows
else
    echo " > build file did not exist [$steam_wrapper_lib_windows]"
fi
