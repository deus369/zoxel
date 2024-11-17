#!/bin/bash

# ssh_key_location=$HOME/.ssh/zoxel
sshname_path="$HOME/.ssh/sshname.txt"
# sshname="zoxel"

# if file doesn't exist, ask user for info
if [ -f "$sshname_path" ]; then
    echo "Loaded ssh name from [$sshname_path]."
    sshname=$(cat "$sshname_path")
else
	source bash/git/git_set_ssh.sh
fi

echo "SSH Name is [$sshname]"
ssh_key_location=$HOME/.ssh/$sshname


echo "Adding ssh key [$ssh_key_location]"
sleep 1

# ssh-add $ssh_key_location

eval "$(ssh-agent -s)"
ssh-add $ssh_key_location
ssh -T git@github.com

sleep 2

echo "Testing connection [git@github.com]"
sleep 1
ssh -T git@github.com
sleep 2

echo "Testing connection [git@codeberg.org]"
sleep 1
ssh -T git@codeberg.org
sleep 2

echo "Tested connections."
sleep 10
