#!/bin/bash
verbose_level=0 # default level
echo_2() {
    local message="$1"
    if [ $verbose_level -eq 1 ]; then
        echo "$message"
    fi
}
