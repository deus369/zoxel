#!/bin/bash

current_directory=$(pwd)
echo Inside $current_directory
sleep 3

source android_copy_source.sh

source gradle_install_debug.sh

echo =====

sleep 3

echo Running logcat

sleep 3

cd $current_directory

source read_logcat.sh

echo Finished running latest

sleep 30