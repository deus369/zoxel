#!/bin/bash

# Function to check if a command is installed
check_command() {
    if ! command -v "$1" &> /dev/null
    then
        echo "$1 could not be found. Please install $1 and try again."
        exit 1
    fi
}

is_ddterm_running() {
    return 0 # cant work out yet how to check
}

check_command ydotool


execute_command_by_ddterm() {
    if command -v "$1" &> /dev/null
    then
        return
    fi
    if command -v "$2" &> /dev/null
    then
        return
    fi
    # opens ddterm
    #if ! is_ddterm_running; then
    #fi

    ydotool key F12 # Open dterm
    sleep 1 # Wait for ddterm to open
    ydotool key Enter
    sleep 1 # Wait for ddterm to open
    ydotool type --delay 100 'clear'
    ydotool key Enter
    sleep 1 # Wait for ddterm to open

    ydotool key Enter
    ydotool type --delay 100 'cd "/home/deus/projects/zoxel"'
    ydotool key Enter

    # Use xdotool to type a command in the dterm window
    ydotool type --delay 100 "$1"
    ydotool key Enter
    sleep $2 # delay by second input
    # can we read terminal output here to see if its building?

    # Closes dterm
    ydotool key F12
    sleep 1
}

execute_command_by_ddterm 'make && make run' 2
# execute_command_by_ddterm 'make dev && make run-valgrind' 6

# Fullscreens Zoxel
ydotool key F11
