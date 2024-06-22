#!/bin/bash

has_yay() {
    if command -v yay >/dev/null 2>&1; then
        echo "  > yay command exists"
        return 0
    else
        echo "  > yay command does not exist"
        return 1
    fi
}

is_steam_deck() {
    if [[ $(uname -m) == "x86_64" && $(cat /sys/class/dmi/id/sys_vendor) == "Valve" ]]; then
        echo "  > steam deck detected"
        return 0
    else
        echo "  - not on steam deck"
        return 1
    fi
}

is_using_pacman() {
    if command -v pacman >/dev/null 2>&1; then
        echo "  > pacman being used"
        return 0
    else
        echo "  - using apt-get"
        return 1
    fi
}

function has_library {
    libraries=("$@")
    for library in "${libraries[@]}"; do
        if command -v dpkg &>/dev/null; then
            if dpkg -s "$library" > /dev/null 2>&1; then
                echo "  [$library] is installed with dpkg"
                return 0
            fi
        fi
        if command -v pacman &>/dev/null; then
            if ! pacman -Q "$library" 2>&1 | grep -q "was not found"; then
                echo "  [$library] is installed with pacman"
                return 0
            fi
        fi
        if command -v yay &>/dev/null; then
            if yay -Q "$library" &>/dev/null; then
                echo "  [$library] is installed with yay"
                return 0
            fi
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
    elif command -v yay >/dev/null 2>&1; then
        yay -S --noconfirm "$library" || return 1
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
        echo "  > library [${libraries[@]}] already exists"
        return 0
    fi
    echo "  > Installing librarys ["${libraries[@]}"] from list"
    for library in "${libraries[@]}"; do
        if install_library "$library"; then
            return 0
        fi
    done
    return 1
}
