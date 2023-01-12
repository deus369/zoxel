#!/bin/bash

ssh_key_location=$HOME/.ssh/zoxel
echo "Adding ssh key [$ssh_key_location]"
sleep 1
ssh-add $ssh_key_location
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