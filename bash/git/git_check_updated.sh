#! /bin/bash

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

echo Finished Checking

# sleep 16
