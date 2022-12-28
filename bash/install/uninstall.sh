#!/bin/bash

zoxel_install_directory=/usr/games/zoxel
shortcut_file_name=zoxel.desktop
# shortcut_directory=/usr/share/applications
shortcut_directory=$HOME/.local/share/applications

# In directory [$pwd] - 
echo "Uninstalling Zoxel"

if [[ -d $zoxel_install_directory ]]; then
    echo "  Removing Zoxel Directory at [$zoxel_install_directory]"
    sudo rm -R $zoxel_install_directory
else
	echo "  Zoxel is not installed at [$zoxel_install_directory]"
fi

if [[ -f $shortcut_directory/$shortcut_file_name ]]; then
    echo "  Removing Shortcut at [$shortcut_directory/$shortcut_file_name]"
    sudo rm $shortcut_directory/$shortcut_file_name
else
	echo "  Zoxel Shortcut is not installed at [$zoxel_install_directory]"
fi

echo "Finished uninstalling Zoxel"