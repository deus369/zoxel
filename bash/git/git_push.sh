#! /bin/bash

ssh_key_location=$HOME/.ssh/zoxel
echo "-> Connecting to Git with ssh key [$ssh_key_location]"
if [ -f $ssh_key_location ]; then
	echo "	- SSH Key found at [$ssh_key_location]"
else
	echo "	- SSH Key not found at [$ssh_key_location]"
	sleep 6
	exit
fi
eval "$(ssh-agent -s)"
ssh-add $ssh_key_location
ssh -T git@github.com
cd $HOME/zoxel
echo "-> Getting modified or updated git files."
modified_and_new_files="$(git ls-files --modified --others --exclude-standard)"
if [ -z "$modified_and_new_files" ]; then
	echo ""
	echo "========================="
	echo "-> No files have been updated."
	echo ""
	echo ""
	echo "========================="
	echo ""
	sleep 6
	exit
else
	# echo "Files have been modified or added."
	echo ""
	echo "========================="
	echo ""
	echo "-> Modified:"
	git ls-files --modified
	echo ""
	echo "-> New:"
	git ls-files --others --exclude-standard
	echo ""
	echo "========================="
	echo ""
	# echo $modified_and_new_files
fi
sleep 1
echo "-> Enter your commit message"
read commitmsg # get commit message off user
echo "	- Commit message is [$commitmsg]"
git add -A	# add all files to staged list
git commit -m "$commitmsg"	# create commit
echo "	- Created commit."
sleep 1
# finally push the git change
git push -u origin master
echo Finished Git Push
sleep 10

# filesUpdated2=$(git diff --name-only)
# if [ -z "$filesUpdated2" ]; then
# 	echo "No files have been updated."
# 	sleep 6
# 	exit
# else
# 	echo "Files have been updated but not commited."
# 	echo $filesUpdated2
# fi
# filesUpdated="$(git ls-files -o)"