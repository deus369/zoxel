#!/bin/bash

echo " > uploading package to steam"
steam_depot_zip="build/steam_export.zip"
vdf_file="$PWD/bash/steam/zoxel.vdf"
# Check if --default flag is provided
if [[ $1 == "--default" ]]; then
    echo "====== UPLOADING TO DEFAULT BRANCH ======"
    vdf_file="$PWD/bash/steam/zoxel_default.vdf"
    echo "====== ====== $vdf_file ====== ======"
else
    echo "====== UPLOADING TO BETA DEFAULT ======"
    echo "====== ====== $vdf_file ====== ======"
fi

read -p " > steam username " username
read -s -p  " > steam password " password

# login anonymous
./build/steamcmd/steamcmd.sh +login $username $password +run_app_build_http $vdf_file +quit

echo " > if wanting default branch, edit [$vdf_file] >setlive< value"
echo "  > next go to https://partner.steamgames.com/apps/builds/1412400 and set build manually"

# xdg-open https://partner.steamgames.com/apps/depotuploads/1412400 &
# echo "build/steam_export.zip" | xclip -selection clipboard
