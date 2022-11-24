#!/bin/bash

cd ~/.ssh

echo "Enter your ssh name"

read sshname

echo "SSH Name is [$sshname]"

# Start Agent, add ssh to agent
eval `ssh-agent`
ssh-add ~/.ssh/$sshname
# next push your first commit

echo "Agent added."

sleep 10
