#!/bin/bash

is_github=false

is_xclip=$(command -v xclip)
if [[ $is_xclip = "" ]]; then
    echo "xclip does not exist. Installing."
    sudo apt-get install xclip
else
    echo "xclip does exist."
fi

is_ssh_keygen=$(command -v ssh-keygen)
if [[ $is_ssh_keygen = "" ]]; then
    echo "ssh-keygen does not exist. Installing."
    sudo apt-get install ssh-keygen
else
    echo "ssh-keygen does exist."
fi

cd ~

if [[ -d .ssh ]]; then
    echo ".ssh exists."
else
    echo ".ssh does not exist. Making."
    mkdir .ssh
fi

cd ~/.ssh

echo "Enter your ssh name"

read sshname

echo "SSH Name is [$sshname]"

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
open https://github.com/settings/keys
sleep 6

echo "Go to https://github.com/settings/keys and paste the ssh key."
echo "Click New SSH key button to add it. Give it the name [$sshname] for consistency."
open https://codeberg.org/user/settings/keys
sleep 6

echo Finished!
sleep 6


# create ssh key
# stackoverflow how to execute ssh keygen without prompt
#ssh-keygen || $sshname
# ssh-keygen -q -t rsa -N '' -f "/$sshname" <<<y >/dev/null 2>&1

# ssh-keygen -q -t rsa -N '' -f "/$sshname" <<< y