#!/bin/sh

#echo " > copying [linux] contents to build/steam_export"
#echo " > copying [windows] contents to build/steam_export"
#echo " > copying [bash/steam/real_steam_appid.txt] contents to build/steam_export/steam_appid.txt"
#echo " > zipping contents"

steam_depot_dir="build/steam_export"
steam_depot_zip="build/steam_export.zip"
windows_dir="build/windows"
linux_dir="build/linux"

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

# first make a directory
echo " > creating [$steam_depot_dir]"
mkdir $steam_depot_dir
cp bash/steam/steam_appid.txt $steam_depot_dir/steam_appid.txt

# Copy files from the Windows directory
echo " > copying files from Windows directory"
cp -r $windows_dir/* $steam_depot_dir/
# Copy the 'zoxel' directory from the Linux directory
echo " > copying 'zoxel' files from [$linux_dir] directory"
cp $linux_dir/zoxel $steam_depot_dir/zoxel
cp $linux_dir/lib/libsteam_api.so $steam_depot_dir/lib/libsteam_api.so
cp $linux_dir/lib/libsteam_wrapper.so $steam_depot_dir/lib/libsteam_wrapper.so

echo " > copying [lib/*.so] contents"
cp lib/*.so $steam_depot_dir/
echo " > copying [lib/*.dll contents"
cp lib/*.dll $steam_depot_dir/

# next zip them
echo " > ziping contents too"
cd $windows_dir && zip -r ../../$steam_depot_zip * && cd ../..
cd $linux_dir && zip -r ../../$steam_depot_zip zoxel && cd ../..
cd $linux_dir && zip -r ../../$steam_depot_zip libsteam_api.so && cd ../..
cd $linux_dir && zip -r ../../$steam_depot_zip libsteam_wrapper.so && cd ../..

echo " > Copying complete. Your files await deployment, My Lord."
