#!/bin/bash
echo " + installing waydroid for android emulation"
sudo apt install curl ca-certificates
curl https://repo.waydro.id | sudo bash
sudo apt install waydroid
echo " > after click download to install android vanilla os"
echo " > test with [adb devices]"
echo " > after install using [make android-install]"
waydroid first-launch
