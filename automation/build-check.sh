#! /bin/bash

echo "Doing a build test!"

cd ..

make -B -j24

echo "Finished Building. Please check for Errors."

sleep 30