#!/bin/bash
# copies zoxel binary, resources folder, and game icon

# Exec=/usr/games/zoxel/zoxel
# cd ../../
echo "Installing Zoxel from zoxel directory [$PWD]"
zoxel_directory=$PWD
shortcut_file_name=zoxel.desktop
# shortcut_directory=/usr/share/applications
shortcut_directory=$HOME/.local/share/applications
# echo "Filename [$file_name]"
binary_path=$zoxel_directory/build/zoxel
resources_directory=$zoxel_directory/build/resources
game_icon_file_name=$resources_directory/textures/game_icon.png
zoxel_install_directory=/usr/games/zoxel
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
sudo cp $binary_path $zoxel_install_directory/$file_name
sudo cp -R $resources_directory $zoxel_install_directory/resources
sudo cp $game_icon_file_name $zoxel_install_directory/zoxel_icon.png
echo "  Copying shortcut [$shortcut_file_name] to [$shortcut_directory]"
sudo cp $zoxel_directory/bash/install/$shortcut_file_name $shortcut_directory/$shortcut_file_name

zoxel_run_bash=/etc/profile.d/zoxel.sh
# Check if /usr/games/zoxel is in the PATH
if [[ ":$PATH:" != *":$zoxel_install_directory:"* ]]; then
    # If it's not in the PATH, add it to the end
    echo "Adding $zoxel_install_directory to PATH"
    # export PATH="$PATH:$zoxel_install_directory"
    sudo touch $zoxel_run_bash
    echo "#!/bin/bash" | sudo tee $zoxel_run_bash
    echo "export PATH=\$PATH:$zoxel_install_directory" | sudo tee -a $zoxel_run_bash
    sudo chmod +x $zoxel_run_bash
    source $zoxel_run_bash
else
    echo "$zoxel_install_directory is already in PATH"
fi

# xdg-open $shortcut_directory

echo "Finished installing Zoxel"