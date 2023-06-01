#!/bin/bash

is_steam_deck() {
    if [[ $(uname -m) == "x86_64" && $(cat /sys/class/dmi/id/sys_vendor) == "Valve" ]]; then
        echo "  > steam deck detected"
        return 0
    else
        echo "  - not on steam deck"
        return 1
    fi
}

function has_library {
    libraries=("$@")
    for library in "${libraries[@]}"; do
        if dpkg -s "$library" > /dev/null 2>&1 || pacman -Qs "$library" > /dev/null 2>&1; then
            echo "  [$library] is installed"
            return 0
        fi
    done
    return 1
}

function install_library {
    library=$1
    if command -v apt-get >/dev/null 2>&1; then
        sudo apt-get install -y "$library" || return 1
    elif command -v pacman >/dev/null 2>&1; then
        sudo pacman -S --noconfirm "$library" || return 1
    else
        echo "  - package manager not found"
        return 1
    fi
    return 0
}

function install_first_library {
    # echo "  > install_first_library"
    libraries=("$@")
    if has_library "${libraries[@]}"; then
        # echo "  > library already exists"
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