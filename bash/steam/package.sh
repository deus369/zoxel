#!/bin/sh
steam_depot_dir="build/steam_export"
steam_depot_zip="build/steam_export.zip"
windows_dir="build/windows"
linux_dir="build/linux"

# removes last build files
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

# creates export directory
echo " > creating [$steam_depot_dir]"
mkdir $steam_depot_dir

# copy in our steam app id
cp bash/steam/steam_appid.txt $steam_depot_dir/steam_appid.txt

# Copy files from the Windows directory
echo " > copying files from Windows directory"
cp -r $windows_dir/* $steam_depot_dir/

# Copy files from the Linux directory
echo " > copying 'zoxel' files from [$linux_dir] directory"
cp -r $linux_dir/* $steam_depot_dir/

# a fix on steam linux libraries (.so files)
# needs to be in run directory apparently
cp lib/*.so $steam_depot_dir/

# zip the export directory
echo " > ziping [$steam_depot_dir] to [$steam_depot_zip]"
cd $steam_depot_dir && zip -r ../../$steam_depot_zip * && cd ../..

echo " > Copying complete. Your files await deployment, My Lord."
