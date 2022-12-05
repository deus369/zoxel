#!/bin/bash

cd ~/zoxel/bash/install/

file_name=zoxel

echo Filename [$file_name]

binary_path=$HOME/zoxel/builds/$file_name

install_path=/usr/games/$file_name

echo Copying $binary_path to $install_path

sudo cp $binary_path $install_path

shortcut_file_name=zoxel.desktop

echo Copying shortcut [$shortcut_file_name] to ~/.local/share/applications/

cp $shortcut_file_name ~/.local/share/applications/$shortcut_file_name

game_icon_file_name=/home/deus/zoxel/builds/resources/textures/game_icon.png

sudo cp $game_icon_file_name /usr/games/zoxel_icon.png

echo "Copied $filename to ~/.local/share/applications"

sleep 6
