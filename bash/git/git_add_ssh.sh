#! /bin/bash

ssh_key_location=$HOME/.ssh/zoxel

echo "-> Connecting to Git with ssh key [$ssh_key_location]"
if [ -f $ssh_key_location ]; then
	echo "	- SSH Key found at [$ssh_key_location]"
else
	echo "\nSSH Key not found at [$ssh_key_location]\n"
	sleep 6
	exit
fi
eval "$(ssh-agent -s)"
ssh-add $ssh_key_location
ssh -T git@github.com
