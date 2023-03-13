#! /bin/bash

sshname_path="$HOME/.ssh/sshname.txt"
# sshname="zoxel"

# if file doesn't exist, ask user for info
if [ -f "$sshname_path" ]; then
    echo "Loaded ssh name from [$sshname_path]."
    sshname=$(cat "$sshname_path")	
else
	# save ssh name for future pushes
	# echo "Enter your ssh name (name of machine):"
	# read sshname
    # echo $sshname > "$sshname_path"
	source git_set_ssh.sh
fi

echo "SSH Name is [$sshname]"
ssh_key_location=$HOME/.ssh/$sshname

echo "-> Connecting to Git with ssh key [$ssh_key_location]"
if [ -f $ssh_key_location ]; then
	echo "	- SSH Key found at [$ssh_key_location]"
else
	echo "	- SSH Key not found at [$ssh_key_location]\n"
	sleep 6
	exit
fi
eval "$(ssh-agent -s)"
ssh-add $ssh_key_location
ssh -T git@github.com
