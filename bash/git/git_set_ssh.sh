#! /bin/bash

sshname_path="$HOME/.ssh/sshname.txt"
echo "Enter your ssh name (name of machine):"
read sshname
echo $sshname > "$sshname_path"
