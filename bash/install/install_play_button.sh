#!/bin/bash

source bash/util/package_util.sh
install_first_library "freeglut3-dev" # installs glut

echo "  > building play button app to [build/play_button]"
gcc tests/glut/play_button.c -o build/play_button -lglut -lGL -lGLU

echo "  > installing play button to [/usr/local/games/zoxel/play_button]"
cp build/play_button /usr/local/games/zoxel/play_button

echo "  > installing desktop shortcut to [$HOME/.local/share/applications/zoxel_play_button.desktop]"
cp bash/install/zoxel_play_button.desktop $HOME/.local/share/applications/zoxel_play_button.desktop