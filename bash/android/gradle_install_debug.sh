#!/bin/bash

source gradle_set_paths.sh

cd $android_directory

# ./gradlew installDebug --debug --stacktrace

# ./gradlew installDebug --debug # --stacktrace

./gradlew installDebug # --debug  --stacktrace

echo Finished Installing Debug Zoxel Android

sleep 15
