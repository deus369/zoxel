#!/bin/bash

function install_library {
    library=$1

    if dpkg -s "$library" > /dev/null 2>&1; then
        echo "[$library] is already installed."
    else
        echo "Installing [$library]..."
        sudo apt-get install -y "$library"
    fi
}

# if arm
install_library "libsdl2-dev"
install_library "libsdl2-image-dev"
install_library "libsdl2-mixer-dev"

# if x86_64
# sudo apt-get install sdl2
# sudo apt-get install libsdl2