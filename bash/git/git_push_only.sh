#! /bin/bash

source git_check_user.sh
ssh_key_location=$HOME/.ssh/zoxel
cd ../../
echo "Inside Directory [$PWD]" # should be zoxel directory

if [[ -f $ssh_key_location ]]; then
	echo "SSH Key found at [$ssh_key_location]"
else
	echo "SSH Key not found at [$ssh_key_location]"
	sleep 6
	exit
fi

echo Connecting to Git with ssh key [$ssh_key_location]
eval "$(ssh-agent -s)"
ssh-add $ssh_key_location
ssh -T git@github.com
echo "Pushing any git commits to origin master"
git push -u origin master
echo Finished Git Push