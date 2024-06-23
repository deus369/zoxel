#!/bin/bash
flecs_install_directory="include/flecs"

download_flecs_source() {
    local version=$1
    if [ -d "$flecs_install_directory" ]; then
        echo "  > flecs [v$version] already exists" >&2
        return
    fi
    # check if include directory exists
    if [ ! -d "$flecs_install_directory" ]; then
        # create include directory if it does not exist
        mkdir -p include
    fi
    # check if include/flecs directory exists
    if [ ! -d "$flecs_install_directory" ]; then
        # create include/flecs directory if it does not exist
        mkdir -p include/flecs
    fi
    # check if flecs.c and flecs.h already exist in include/flecs
    if [ ! -f "$flecs_install_directory/flecs.c" ] || [ ! -f "$flecs_install_directory/flecs.h" ]; then
        echo "  > downloading flecs [v$version]" >&2
        # download zip file
        wget https://github.com/SanderMertens/flecs/archive/refs/tags/v$version.zip >&2
        # extract zip file
        unzip -j v$version.zip flecs-$version/flecs.c flecs-$version/flecs.h -d include/flecs >&2
        # delete downloaded zip and extracted folder
        rm v$version.zip
    fi
	# cp $flecs_install_directory/flecs.h include
    echo "  > flecs [v$version] source is downloaded" >&2
}
