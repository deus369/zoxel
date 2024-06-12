#!/bin/sh

source bash/util/package_util.sh

# installing yay for steamcmd
echo " > installing steamcmd requirements"
if [ -f "/etc/ld.so.conf.d/fakeroot.conf" ]; then
    sudo rm /etc/ld.so.conf.d/fakeroot.conf
fi
# sudo pacman -S base-devel # this should be installed prior?
# install_library "pacman"
install_library "fakeroot"
install_library "libarchive"
install_library "makepkg"

# if on arch linux
echo " > installing yay"
cd $HOME/projects
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si

# if ubuntu with apt
sudo apt install -y git perl
cd $HOME/projects
git clone https://aur.archlinux.org/trizen.git
cd trizen
makepkg -si



echo " > installing steamcmd with yay"
yay -S steamcmd
