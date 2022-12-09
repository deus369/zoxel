#! /bin/bash

echo Running git_push.sh!

ssh_key_location=$HOME/.ssh/zoxel
if [ -f $ssh_key_location ]; then
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

echo "Getting modified or updated git files."
modified_and_new_files="$(git ls-files --modified --others --exclude-standard)"
# filesUpdated="$(git ls-files -o)"

if [ -z "$modified_and_new_files" ]; then
	echo "No files have been updated."
	sleep 6
	exit
	# filesUpdated2=$(git diff --name-only)
	# if [ -z "$filesUpdated2" ]; then
	# 	echo "No files have been updated."
	# 	sleep 6
	# 	exit
	# else
	# 	echo "Files have been updated but not commited."
	# 	echo $filesUpdated2
	# fi
else
	echo "Files have been modified or added."
	echo ""
	echo "========================="
	# git ls-files --modified --others --exclude-standard
	echo ""
	echo "Modified:"
	git ls-files --modified
	echo ""
	echo "New:"
	git ls-files --others --exclude-standard
	echo ""
	echo "========================="
	echo ""
	# echo $modified_and_new_files
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