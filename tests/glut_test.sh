#!/bin/bash

gcc -o tests/glut_test tests/glut_test.c -lGL -lGLU -lglut

if [ $? -eq 0 ]; then
    ./tests/glut_test
    # rm tests/sdl_test
else
    echo "Compilation failed."
fi

sleep 666