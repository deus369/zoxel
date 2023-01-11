#!/bin/bash

install_location=$HOME/.profile #.bash_profile
run_command="x-terminal-emulator -f -e '$HOME/zoxel/documents/zoxel_web/run_latest.sh'"

if [ ! -f $install_location ]
then
    echo ".bash_profile file does not exist."
    sleep 12
    exit
fi

# Check if the command is present in .bash_profile
if [[ $(grep "$run_command" $install_location) == $run_command ]]
then
    # Command is present, so remove it
    converted_string=$(echo "$run_command" | sed -e 's/[$]/\\$/g' -e 's/[\/]/\\\//g')
    sed -i "/$converted_string/d" $install_location
    echo "Command removed from .bash_profile [$run_command] -> [$converted_string]"
else
    # Command is not present
    echo "Command not found in .bash_profile [$run_command]"
fi


sleep 22