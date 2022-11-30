#! /bin/bash

cd ~/zoxel

echo Connecting to Git First

eval "$(ssh-agent -s)"

ssh-add ~/.ssh/zoxel

ssh -T git@github.com

# create commit
git commit -m "$commitmsg"

# finally push the git change
git push -u origin master

echo Finished Git Push

sleep 10
