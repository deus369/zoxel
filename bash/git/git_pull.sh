#! /bin/bash

cd ../../

ssh_key_location=$HOME/.ssh/zoxel
echo "Adding ssh key for github [$ssh_key_location]."
ssh-add $ssh_key_location
ssh -T git@github.com

git pull

echo "Finished git pull."

sleep 10