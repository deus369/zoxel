#! /bin/bash

source git_check_user.sh
source git_add_ssh.sh
echo "Pushing any git commits to origin master"
git push -u origin master