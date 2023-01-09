#!/bin/bash

install_location=$HOME/.profile #.bash_profile
run_command="gnome-terminal --full-screen -e '$HOME/zoxel/documents/zoxel_web/run_latest.sh'"

# Check if the $install_location file exists
if [ ! -f $install_location ]
then
    # $install_location file does not exist, so create it
    touch $install_location
    echo "Created $install_location file"
else
    echo "$install_location file exists."
fi

# Check if the command has already been added to $install_location
if [[ $(grep "$run_command" $install_location) == $run_command ]]
then
    # Command already added
    echo "Command already added to $install_location"
else
    # Command not added, so add it
    echo $run_command >> $install_location
    echo "Command added to $install_location"
fi

sleep 22