#!/bin/bash
lib="lib"
windows_threads_dll="bash/windows/libwinpthread-1.dll"
if [ ! -f $lib/libwinpthread-1.dll ]; then
    echo " + copying [$windows_threads_dll] to [$lib/libwinpthread-1.dll]"
    cp $windows_threads_dll $lib/libwinpthread-1.dll
else
    echo " > [$lib/libwinpthread-1.dll] already exists"
fi
