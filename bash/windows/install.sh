#!/bin/bash
# copies zoxel binary, resources folder, and game icon
zoxel_install_directory="C:/Program Files/zoxel"
zoxel_build_directory="build/windows"
# Destination folder for the shortcut
# C:\Users\deus3\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\
shortcut_directory="$APPDATA/Microsoft/Windows/Start Menu/Programs/zoxel"
app_filepath="$zoxel_install_directory/zoxel.exe"

if [[ -d "$zoxel_install_directory" ]]; then
	echo " > removing old installation [$zoxel_install_directory]"
    rm -R "$zoxel_install_directory"
else
    if [[ -f "$zoxel_install_directory" ]]; then
        echo "  + directory existed as a file? [$zoxel_install_directory]"
        rm "$zoxel_install_directory"
    fi
fi


echo " + creating install directory [$zoxel_install_directory]"
mkdir "$zoxel_install_directory"
echo "  + copying to install directory [$zoxel_install_directory]"
cp -r "$zoxel_build_directory/"* "$zoxel_install_directory/"

#shortcut

if [[ -d "$zoxel_install_directory" ]]; then
	echo " > removing old shortcut directory [$shortcut_directory]"
    rm -R "$shortcut_directory"
fi


echo " > creating shortcut directory [$shortcut_directory]"
mkdir "$shortcut_directory"

# copy shortcut into that folder
cp "bash/windows/zoxel.ico" "$zoxel_install_directory/zoxel.ico"
cp "bash/windows/zoxel.lnk" "$shortcut_directory/zoxel.lnk"
