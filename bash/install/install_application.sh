#!/bin/bash

cd ~/zoxel/bash/install/

filename=zoxel_git.desktop

echo Filename is $filename

cp $filename ~/.local/share/applications/$filename

echo "Copied $filename to ~/.local/share/applications"

sleep 6
