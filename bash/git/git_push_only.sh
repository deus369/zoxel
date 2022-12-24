#! /bin/bash

source git_check_user.sh

ssh_key_location=$HOME/.ssh/zoxel
if [[ -f $ssh_key_location ]]; then
	echo "SSH Key found at [$ssh_key_location]"
else
	echo "SSH Key not found at [$ssh_key_location]"
	sleep 10
	exit
fi

echo Connecting to Git with ssh key [$ssh_key_location]
eval "$(ssh-agent -s)"
ssh-add $ssh_key_location
ssh -T git@github.com

echo "Pushing any commits to git [$HOME/zoxel] origin master"
cd $HOME/zoxel
# create commit
# git commit -m "$commitmsg"
# finally push the git change
git push -u origin master
echo Finished Git Push
sleep 10