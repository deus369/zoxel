#!/bin/sh

# open downloaded steamworks
#  copy .so / .dll files into lib
#  copy steam directory in include

echo " > download from [https://partner.steamgames.com/downloads/list]"

sdk_zip="$HOME/Downloads/steamworks_sdk.zip" # steamworks_sdk_158a.zip"
include_dest="include/steam"
lib_dest="lib/libsteam_api.so"
lib_dest2="lib/steam_api64.dll"
app_id="bash/steam/steam_appid.txt"
app_id_dest="build/steam_appid.txt"

echo "  > sdk_zip set to [$sdk_zip]"
if [ ! -f $sdk_zip ]; then
    echo " ! sdk file not found"
    exit
fi

echo "      > include_dest [$include_dest]"
echo "      > lib_dest [$lib_dest]"

echo "  > removing old steam_sdk files"
rm -r $include_dest
rm $lib_dest
rm $lib_dest2
rm $app_id_dest

if [ ! -d include ]; then
    mkdir include
fi
mkdir -p "$include_dest"
if [ ! -d lib ]; then
    mkdir lib
fi
if [ ! -d build ]; then
    mkdir build
fi

# Extract header files
echo " > extracting for [$include_dest]"
unzip -o "$sdk_zip" 'sdk/public/steam/*.h' -d "/tmp"
mv "/tmp/sdk/public/steam/"* "$include_dest"

# Extract the libsteam_api.so file
echo " > extracting for [$lib_dest]"
unzip -o "$sdk_zip" 'sdk/redistributable_bin/linux64/libsteam_api.so' -d "/tmp"
mv "/tmp/sdk/redistributable_bin/linux64/libsteam_api.so" "$lib_dest"

# Extract the libsteam_api.so file
echo " > extracting for [$lib_dest2]"
unzip -o "$sdk_zip" 'sdk/redistributable_bin/win64/steam_api64.dll' -d "/tmp"
mv "/tmp/sdk/redistributable_bin/win64/steam_api64.dll" "$lib_dest2"

echo "      > copying [$app_id] to [$app_id_dest]"
cp $app_id $app_id_dest
