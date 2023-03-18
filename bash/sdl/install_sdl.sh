#!/bin/bash

function has_library {
    libraries=("$@")
    found=0
    for library in "${libraries[@]}"; do
        if dpkg -s "$library" > /dev/null 2>&1 || pacman -Qs "$library" > /dev/null 2>&1; then
            echo "[$library] is already installed."
            found=1
            break
        fi
    done
    return $found
}

function install_library {
    library=$1
    if command -v apt-get >/dev/null 2>&1; then
        sudo apt-get install -y "$library"
    elif command -v pacman >/dev/null 2>&1; then
        sudo pacman -S --noconfirm "$library"
    else
        echo "Package manager not found!"
        return 1
    fi
    return 0
}

function install_first_library {
    echo "  > install_first_library"
    libraries=("$@")
    if has_library "${libraries[@]}"; then
       return 0
    fi
    echo "  > Installing library from list"
    for library in "${libraries[@]}"; do
        if install_library "$library"; then
            return 0
        fi
    done
    return 1
}

install_first_library "libsdl2-dev" "SDL2-devel" "libsdl2" "libsdl2-2.0" "sdl2"
install_first_library "libsdl2-image-dev" "SDL2_image-devel" "libsdl2_image" "libsdl2-image-2.0" "sdl2_image"
install_first_library "libsdl2-mixer-dev" "SDL2_mixer-devel" "libsdl2_mixer" "libsdl2-mixer-2.0" "sdl2_mixer"

# if arm
# install_library "libsdl2-dev"
# install_library "libsdl2-image-dev"
# install_library "libsdl2-mixer-dev"
# if other
# install_library "SDL2-devel"
# install_library "SDL2_image-devel"
# install_library "SDL2_mixer-devel"

# if x86_64
# sudo apt-get install sdl2
# sudo apt-get install libsdl2

# function install_library {
#     library=$1
#     if dpkg -s "$library" > /dev/null 2>&1; then
#         echo "[$library] is already installed."
#     else
#         echo "Installing [$library]..."
#         sudo apt-get install -y "$library"
#     fi
# }

# function install_library {
#     library=$1
#     if dpkg -s "$library" > /dev/null 2>&1 || pacman -Qs "$library" > /dev/null 2>&1; then
#         echo "[$library] is already installed."
#     else
#         echo "Installing [$library]..."
#         if command -v apt-get >/dev/null 2>&1; then
#             sudo apt-get install -y "$library"
#         elif command -v pacman >/dev/null 2>&1; then
#             sudo pacman -S --noconfirm "$library"
#         else
#             echo "Package manager not found!"
#             exit 1
#         fi
#     fi
# }