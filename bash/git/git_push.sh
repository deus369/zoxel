#! /bin/bash

echo Connecting to Git First

eval "$(ssh-agent -s)"

ssh-add ~/.ssh/zoxel

ssh -T git@github.com

# sleep 3

cd ~/zoxel

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
