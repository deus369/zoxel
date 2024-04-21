#! /bin/bash

# cd ~/zoxel/src

# git ls-files | grep '\.c' | xargs wc -l

git ls-files --full-name | grep '^src/.*\.c$' | xargs wc -l
