#!/bin/bash

echo "  > uninstalling zoxel"
# install_directory="/usr/games"
install_directory="/usr/local/games"
echo "  > install directory is [$install_directory]"
zoxel_install_directory=$install_directory/zoxel
shortcut_file_name=zoxel.desktop
# shortcut_directory=/usr/share/applications
shortcut_directory=$HOME/.local/share/applications
old_zoxel_install_directory=/usr/games/zoxel

if [[ -d $zoxel_install_directory ]]; then
    echo "  > removing zoxel directory at [$zoxel_install_directory]"
    sudo rm -R $zoxel_install_directory
else
	echo "  Zoxel is not installed at [$zoxel_install_directory]"
fi

if [[ -d $old_zoxel_install_directory ]]; then
    echo "  - removing old zoxel directory at [$old_zoxel_install_directory]"
    sudo rm -R $old_zoxel_install_directory
else
	echo "  Zoxel is not installed at [$zoxel_install_directory]"
fi

if [[ -f $shortcut_directory/$shortcut_file_name ]]; then
    echo "  Removing Shortcut at [$shortcut_directory/$shortcut_file_name]"
    sudo rm $shortcut_directory/$shortcut_file_name
else
	echo "  Zoxel Shortcut is not installed at [$zoxel_install_directory]"
fi

echo "  > finished uninstalling Zoxel"