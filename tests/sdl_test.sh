#!/bin/bash

gcc -o tests/sdl_test tests/sdl_test.c -lSDL2

if [ $? -eq 0 ]; then
    ./tests/sdl_test
    # rm tests/sdl_test
else
    echo "Compilation failed."
fi

sleep 666