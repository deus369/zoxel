#! /bin/bash

cd ~/zoxel/src

git ls-files | grep '\.c' | xargs wc -l

sleep 666
