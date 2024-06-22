#!/bin/bash
source bash/util/package_util.sh

if has_library "yay" ; then
    echo "  > library [yay] already exists"
else
    echo "  > library [yay] does not exists"
    echo " > installing yay"
    install_first_library "fakeroot"
    # sudo pacman -S --needed base-devel git
    # if fakeroot fails
    # sudo pacman -Sy --overwrite /etc/ld.so.conf.d/fakeroot.conf fakeroot
    cd ..
    if [ ! -d yay ]; then
        echo " + cloning [https://aur.archlinux.org/yay.git]"
        # git clone https://aur.archlinux.org/yay-bin.git
        git clone https://aur.archlinux.org/yay.git
    fi
    cd yay
    git checkout 17f4503492f5070ebcca58743144773c89099dff # if pacman < 6.1
    makepkg -si --noconfirm
    cd ..
    # rm -rf yay
    cd zoxel
fi

