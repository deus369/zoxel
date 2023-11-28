#!/bin/bash

echo " > uploading package to steam"
steam_depot_zip="build/steam_export.zip"
vdf_file="$PWD/bash/steam/zoxel.vdf"

read -p " > steam username " username
read -s -p  " > steam password " password

steamcmd +login $username $password +run_app_build_http $vdf_file +quit

# force_install_dir $steam_depot_zip
# app_update 1412400 validate
# xdg-open https://partner.steamgames.com/apps/depotuploads/1412400 &
# echo "build/steam_export.zip" | xclip -selection clipboard
