#!/bin/bash

# cd $HOME/zoxel/bash/install/
zoxel_directory=$HOME/zoxel
file_name=zoxel
shortcut_file_name=zoxel.desktop
# echo "Filename [$file_name]"
binary_path=$zoxel_directory/$file_name
install_path=/usr/games/$file_name

# In directory [$pwd] - 
echo "Zoxel directory is [$zoxel_directory]"
echo "Copying $binary_path to $install_path"
sudo cp $binary_path $install_path
echo "Copying shortcut [$shortcut_file_name] to $HOME/.local/share/applications/"
cp $zoxel_directory/bash/install/$shortcut_file_name $HOME/.local/share/applications/$shortcut_file_name
game_icon_file_name=$zoxel_directory/resources/textures/game_icon.png
sudo cp $game_icon_file_name /usr/games/zoxel_icon.png

echo "Finished installing Zoxel"