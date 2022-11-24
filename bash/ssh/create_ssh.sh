#!/bin/bash

cd ~

mkdir .ssh

cd ~/.ssh

echo "Enter your ssh name"

read sshname

echo "SSH Name is [$sshname]"

# create ssh key
# stackoverflow how to execute ssh keygen without prompt
#ssh-keygen || $sshname
# ssh-keygen -q -t rsa -N '' -f "/$sshname" <<<y >/dev/null 2>&1

# ssh-keygen -q -t rsa -N '' -f "/$sshname" <<< y

ssh-keygen -q -N '' -f "$sshname"

echo "Created SSH [$sshname]"

xclip -sel c < $sshname.pub
cat $sshname.pub

echo Finished SSH Create. SSH copied to clipboard.

# Start Agent, add ssh to agent
eval `ssh-agent`
ssh-add ~/.ssh/$sshname
# next push your first commit

echo "Go to https://github.com/settings/keys and paste the ssh key."

echo "Click New SSH key button to add it. Give it the name [$sshname] for consistency."

sleep 10
