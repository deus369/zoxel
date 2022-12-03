#!/bin/bash

source gradle_set_paths.sh

cd $android_directory

./gradlew install #installRelease

echo Finished Installing Release Zoxel Android
sleep 330
