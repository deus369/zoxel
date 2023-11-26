#!/bin/sh
# builds test_steamworks

wrapper_cpp="bash/steam/steamwrapper.cpp"
wrapper_c="bash/steam/steamwrapper.c"
test_wrapper_c="bash/steam/steamwrapper_test.c"
lib_output="lib/libsteam_wrapper.so"
test_output="build/test_steamworks"

# builds library
#builds test_steamworks
echo " > compiling cpp"
g++ -shared $wrapper_cpp -o $lib_output -Iinclude/steam -Llib -lsteam_api -fPIC
echo " > compiling c"
gcc $test_wrapper_c $wrapper_c -o $test_output -Iinclude/steam -Llib -lsteam_api -lsteam_wrapper -Wl,-rpath,'$ORIGIN/lib:$ORIGIN/../lib'

# runs it
./$test_output
