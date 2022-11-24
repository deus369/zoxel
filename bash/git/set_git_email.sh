#!/bin/bash

echo "Enter your git email"

read gitemail

echo "Your git email is [$gitemail]"

sleep 3

git config --global user.email "$gitemail"

echo "Finished setting your git email"

sleep 13