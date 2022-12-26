#!/bin/bash
# copies zoxel binary, resources folder, and game icon

# Exec=/usr/games/zoxel/zoxel
cd ../../
echo "Installing Zoxel from zoxel directory [$PWD]"
# cd $HOME/zoxel/bash/install/
zoxel_directory=$PWD # $HOME/zoxel
shortcut_file_name=zoxel.desktop
shortcut_directory=/usr/share/applications # $HOME/.local/share/applications
# echo "Filename [$file_name]"
binary_path=$zoxel_directory/zoxel
resources_directory=$zoxel_directory/resources
zoxel_install_directory=/usr/games/zoxel
game_icon_file_name=$zoxel_directory/resources/textures/game_icon.png
file_name=zoxel
echo "  Zoxel Directory is: $zoxel_directory"

# make the install location in usr/games/
if [[ -d $zoxel_install_directory ]]; then
	echo "  Install Directory exists [$zoxel_install_directory]"
else
	echo "  Adding Install Directory [$zoxel_install_directory]"
    if [[ -f $zoxel_install_directory ]]; then
        sudo rm $zoxel_install_directory
    fi
    sudo mkdir $zoxel_install_directory
fi

echo "  Copying [$zoxel_directory/$file_name], resources & icon to [$zoxel_install_directory]"
sudo cp $zoxel_directory/$file_name $zoxel_install_directory/$file_name
sudo cp -R $zoxel_directory/resources $zoxel_install_directory/resources
sudo cp $game_icon_file_name $zoxel_install_directory/zoxel_icon.png

echo "  Copying shortcut [$shortcut_file_name] to [$shortcut_directory]"
sudo cp $zoxel_directory/bash/install/$shortcut_file_name $shortcut_directory/$shortcut_file_name

# xdg-open $shortcut_directory

echo "Finished installing Zoxel"