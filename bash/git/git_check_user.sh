#!/bin/bash
# This is used to check git username and email on a new pc during git process.

current_name=$(git config --get user.name)
current_email=$(git config --get user.email)
echo "Current name is $current_name"
echo "Current email is $current_email"
sleep 2

if [[ $current_name = "" ]]; then
    source set_git_name.sh
fi

if [[ $current_email = "" ]]; then
    source set_git_email.sh
fi

echo "Finished checking credentials."