#!/bin/bash

echo "  > uninstalling zoxel"
# install_directory="/usr/games"
install_directory="/usr/local/games"
echo "  > install directory is [$install_directory]"
zoxel_install_directory=$install_directory/zoxel
zoxel_install_directory2=/usr/games/zoxel
shortcut_file_name=zoxel.desktop
# shortcut_directory=/usr/share/applications
shortcut_directory=$HOME/.local/share/applications

if [[ -d $zoxel_install_directory ]]; then
    echo "  > removing zoxel directory at [$zoxel_install_directory]"
    sudo rm -R $zoxel_install_directory
else
	echo "  - zoxel is not installed at [$zoxel_install_directory]"
fi
if [[ -d $zoxel_install_directory2 ]]; then
    echo "  > removing old zoxel directory at [$zoxel_install_directory2]"
    sudo rm -R $zoxel_install_directory2
else
	echo "  - zoxel is not installed at [$zoxel_install_directory2]"
fi

if [[ -f $shortcut_directory/$shortcut_file_name ]]; then
    echo "  > removing shortcut at [$shortcut_directory/$shortcut_file_name]"
    sudo rm $shortcut_directory/$shortcut_file_name
else
	echo "  - zoxel shortcut was not installed at [$zoxel_install_directory]"
fi

echo "  > finished uninstalling Zoxel"