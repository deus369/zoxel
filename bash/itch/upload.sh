#! /bin/bash

echo " [todo] upload game with itch"
butler="./build/butler/butler"
username="deus0"
game="zoxel"
echo " > user is [$username]"
$butler upgrade --assume-yes

# https://deus0.itch.io/zoxel
# butler push <your-game-folder> <itch-username>/<game-slug>:<channel>

windows_build=build/windows
windows_channel="new_win"
echo " > pushing itch io game [$windows_build] to [$game:$windows_channel]"
$butler push $windows_build $username/$game:$windows_channel

linux_build=build/linux
linux_channel="new_lin"
echo " > pushing itch io game [$linux_build] to [$game:$linux_channel]"
$butler push $linux_build $username/$game:$linux_channel
