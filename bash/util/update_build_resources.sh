#!/bin/bash

game="$1"

update_resources() {
    local build_directory="build/$1"
    if [ -d "$build_directory" ]; then
        echo " + updating [$build_directory/resources]"
        rm -R "$build_directory/resources"
        cp -R resources "$build_directory/resources"
    else
        echo " ! build directory did not exist [$build_directory]"
    fi
}

update_resources $game-linux
update_resources $game-windows
