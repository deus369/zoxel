#! /bin/bash

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

cd $HOME/zoxel

filesUpdated="$(git ls-files -o)"

if [ -z "$filesUpdated" ]; then
	filesUpdated2=$(git diff --name-only)
	if [ -z "$filesUpdated2" ]; then
		echo "No files have been updated."
		sleep 6
		exit
	else
		echo "Files have been updated but not commited."
		echo $filesUpdated2
	fi
else
	echo "Files have been updated."
	echo $filesUpdated
fi

# sleep 2
echo "Enter your commit message"
read commitmsg

echo "Commit message is [$commitmsg]"
# add all to changed list
git add -A
# create commit
git commit -m "$commitmsg"

# finally push the git change
git push -u origin master
echo Finished Git Push
sleep 10