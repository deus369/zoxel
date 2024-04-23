#!/bin/bash

web_build_path="build/web"
resources="resources"
build_resources="$web_build_path/resources"

source bash/web/install_sdk.sh

if [ ! -d "$web_build_path" ]; then
    mkdir "$web_build_path"
    echo " + created new build directory [$web_build_path]"
fi


# resources
if [ -d "$build_resources" ]; then
    echo " + removing old resources [$build_resources]"
    rm -rf "$build_resources"
else
    echo " > [$build_resources] did not exist"
fi
echo "copying resourceces into [$build_resources]"
mkdir "$build_resources"
cp -r $resources/* $build_resources/
