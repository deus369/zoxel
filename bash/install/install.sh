#!/bin/bash
# copies zoxel binary, resources folder, and game icon

install_directory_1=/usr/local/games
install_directory_2=/usr/games

echo "  > installing zoxel" #  from zoxel directory [$PWD]"
install_directory=$install_directory_1
echo "  > install directory is [$install_directory]"
# zoxel_directory=$PWD
shortcut_file_name=zoxel_git.desktop
# shortcut_directory=/usr/share/applications
shortcut_directory=$HOME/.local/share/applications
# echo "Filename [$file_name]"
binary_path=build/linux/zoxel
resources_directory=build/resources
# game_icon_file_name=$resources_directory/textures/game_icon.png
zoxel_install_directory=$install_directory/zoxel
install_resource_directory=$zoxel_install_directory/resources
file_name=zoxel
updater_shell_name=bash/install/updater.sh
updater_file_name=zoxel_updater.desktop
# echo "  Zoxel Directory is: $zoxel_directory"

# make the install location in usr/games/
if [[ -d $zoxel_install_directory ]]; then
	echo "  + install directory exists [$zoxel_install_directory]"
else
	echo "  + creating install directory [$zoxel_install_directory]"
    if [[ -f $zoxel_install_directory ]]; then
        rm $zoxel_install_directory
    fi
    sudo mkdir $zoxel_install_directory
    sudo chown -R $USER:$USER "$zoxel_install_directory"
    sudo chmod -R 755 $zoxel_install_directory
fi

if [[ -d $zoxel_install_directory ]]; then
    echo "  + copying [$file_name], resources & icon to [$zoxel_install_directory]"
    cp $binary_path $zoxel_install_directory/$file_name
    if [[ -d $install_resource_directory ]]; then
        echo "  > removing old resources [$install_resource_directory]"
        rm -R $install_resource_directory
    fi
    echo "  + copying [$resources_directory], resources & icon to [$install_resource_directory]"
    cp -R $resources_directory $install_resource_directory
    # echo "  + copying [$game_icon_file_name], resources & icon to [$zoxel_install_directory/zoxel_icon.png]"
    # cp $game_icon_file_name $zoxel_install_directory/zoxel_icon.png
    echo "  + copying shortcut [$shortcut_file_name] to [$shortcut_directory]"
    cp bash/install/$shortcut_file_name $shortcut_directory/$shortcut_file_name
    echo "  + copying [$updater_shell_name] to [$zoxel_install_directory/updater.sh]"
    cp $updater_shell_name $zoxel_install_directory/updater.sh
    echo "  + add executeable permissions to [$zoxel_install_directory/updater.sh]"
    chmod +x $zoxel_install_directory/updater.sh # add executeable permissions to updater.sh
    echo "  + copying updater [bash/install/$updater_file_name] to [$shortcut_directory/$updater_file_name]"
    cp bash/install/$updater_file_name $shortcut_directory/$updater_file_name
else
	echo "  ! failed to create install directory [$zoxel_install_directory]"
fi

source bash/install/install_to_terminal.sh

# xdg-open $shortcut_directory

echo "  > finished installing zoxel"
