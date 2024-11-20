#!/bin/bash
script_directory="$(dirname "$(realpath "$0")")"
project_directory="$script_directory/../.."
cd $project_directory
while true; do
    git pull && make && make package
    echo " > running $script_directory/kill.sh"
    # bash $script_directory/kill.sh
    # run zoxel-web service
    echo "  > running zoxel"
    make run-server
    # Check the exit status to determine if it crashed
    if [[ $? -ne 0 ]]; then
        echo "  > zoxel crashed, restarting..."
    else
        echo "  > finished running zoxel"
    fi
    # Optional: Add a delay to avoid a tight loop in case of frequent crashes
    sleep 10
done
