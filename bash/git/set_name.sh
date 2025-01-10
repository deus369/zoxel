#!/bin/bash

echo "Enter your git name"

read gitname

echo "Your git name is [$gitname]"

git config --global user.name "$gitname"

echo "Finished setting your git name"