#! /bin/bash

echo " [todo] upload game with itch"
butler="./build/butler/butler"
username="deus0"
game="zoxel"

linux_build=build/linux
channel_linux="new_lin"

windows_build=build/windows
channel="new_win"
# https://deus0.itch.io/zoxel
# butler push <your-game-folder> <itch-username>/<game-slug>:<channel>

$butler upgrade --assume-yes
echo " > user is [$username]"
echo " > pushing itch io game [$windows_build] to [$game:$channel]"
$butler push $windows_build $username/$game:$channel
