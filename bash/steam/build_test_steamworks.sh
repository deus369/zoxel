#!/bin/sh
# builds test_steamworks

wrapper_c="bash/steam/steamwrapper.c"
test_wrapper_c="bash/steam/steamwrapper_test.c"
test_output="build/test_steamworks"

echo " > compiling team steamworks [$test_output]"
gcc $test_wrapper_c $wrapper_c -o $test_output -Iinclude/steam -Llib -lsteam_api -lsteam_wrapper -Wl,-rpath,'$ORIGIN/lib:$ORIGIN/../lib'
