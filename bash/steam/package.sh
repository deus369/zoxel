#!/bin/sh

#echo " > todo: this"
#echo " > copying [linux] contents to build/steam_export"
#echo " > copying [windows] contents to build/steam_export"
#echo " > copying [bash/steam/real_steam_appid.txt] contents to build/steam_export/steam_appid.txt"
#echo " > zipping contents"

steam_depot_zip="build/steam_export.zip"
windows_dir="build/windows"
linux_dir="build"

if [ -f $steam_depot_zip ]; then
    echo " > removing last [$steam_depot_zip]"
    rm $steam_depot_zip
else
    echo " > no last zip [$steam_depot_zip]"
fi

# zip -r $steam_depot_zip $windows_dir
# zip $steam_depot_zip $linux_file

cd $windows_dir && zip -r ../../$steam_depot_zip * && cd ../..
cd $linux_dir && zip -r ../$steam_depot_zip zoxel && cd ..

echo " > todo: opening steamworks upload link"
