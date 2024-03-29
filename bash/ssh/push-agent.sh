#!/bin/bash

echo "Pushing ssh agent."

echo "Enter your ssh name"

read sshname

echo "SSH Name is [$sshname]"

# Start Agent, add ssh to agent
cd ~/.ssh
eval `ssh-agent`
ssh-add $sshname
# next push your first commit

echo "Agent added."

echo "Testing connection."

ssh -T git@github.com

echo "Tested connection."

sleep 10
