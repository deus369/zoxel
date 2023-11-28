#!/bin/sh

# installing yay for steamcmd
echo " > installing steamcmd requirements"
sudo rm /etc/ld.so.conf.d/fakeroot.conf
sudo pacman -S fakeroot
# sudo pacman -S base-devel # this should be installed prior?
sudo pacman -S pacman
sudo pacman -S libarchive

echo " > installing yay"
cd $HOME/projects
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si

echo " > installing steamcmd with yay"
yay -S steamcmd
