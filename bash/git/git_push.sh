#! /bin/bash

source bash/git/git_check_user.sh
source bash/git/git_add_ssh.sh

echo "Inside Directory [$PWD]" # should be zoxel directory
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
	git push # -u origin master
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

echo "-> Enter your commit message:"
# get commit message off user
read commitmsg
echo "	> commit message is [$commitmsg]"
# add all files to staged list
git add -A
# create commit
git commit -m "$commitmsg"
echo "	> created commit"
git push # -u origin master


# sleep 1
# finally push the git change
# echo Finished Git Push
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

# is_force=$(false)
# if [[ $1 = "-f" ]]; then
# 	is_force=$(true)
# 	echo "Forcing push."
# 	git push -u origin master
# 	sleep 6
# 	exit
# fi