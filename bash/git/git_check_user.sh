#!/bin/bash
# This is used to check git username and email on a new pc during git process.

echo "  > checking credentials"
current_name=$(git config --get user.name)
current_email=$(git config --get user.email)
echo "      + name is [$current_name]"
echo "      + email is [$current_email]"

if [[ $current_name = "" ]]; then
    source bash/git/set_git_name.sh
fi

if [[ $current_email = "" ]]; then
    source bash/git/set_git_email.sh
fi

echo "  > checking credentials completed"