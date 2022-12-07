#!/bin/bash

file_name=zoxel
shortcut_file_name=zoxel.desktop

# In directory [$pwd] - 
echo "Uninstalling Zoxel"
echo "Removing [/usr/games/$file_name]"
sudo rm /usr/games/$file_name
echo "Removing [/usr/games/zoxel_icon.png]"
sudo rm /usr/games/zoxel_icon.png
echo "Removing [$HOME/.local/share/applications/$shortcut_file_name]"
sudo rm $HOME/.local/share/applications/$shortcut_file_name

echo "Finished uninstalling Zoxel"