#!/bin/sh

#echo " > todo: this"
#echo " > copying [linux] contents to build/steam_export"
#echo " > copying [windows] contents to build/steam_export"
#echo " > copying [bash/steam/real_steam_appid.txt] contents to build/steam_export/steam_appid.txt"
#echo " > zipping contents"

steam_depot_dir="build/steam_depot"
steam_depot_zip="build/steam_export.zip"
windows_dir="build/windows"
linux_dir="build"

if [ -f $steam_depot_zip ]; then
    echo " > removing last [$steam_depot_zip]"
    rm $steam_depot_zip
else
    echo " > no last zip [$steam_depot_zip]"
fi

if [ -d $steam_depot_dir ]; then
    echo " > removing [$steam_depot_dir]"
    rm -R $steam_depot_dir
else
    echo " > no last [$steam_depot_dir]"
fi

cd $windows_dir && zip -r ../../$steam_depot_zip * && cd ../..
cd $linux_dir && zip -r ../$steam_depot_zip zoxel && cd ..

echo " > creating [$steam_depot_dir]"
mkdir $steam_depot_dir
# Copy files from the Windows directory
echo " > copying files from Windows directory"
cp -r $windows_dir/* $steam_depot_dir/
# Copy the 'zoxel' directory from the Linux directory
echo " > copying 'zoxel' directory from Linux directory"
cp -r $linux_dir/zoxel $steam_depot_dir/

echo " > Copying complete. Your files await deployment, My Lord."

# echo " > todo: opening steamworks upload link"

# zip -r $steam_depot_zip $windows_dir
# zip $steam_depot_zip $linux_file
