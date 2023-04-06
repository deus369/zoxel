#!/bin/bash

source bash/flecs/flecs_util.sh
echo "  > check versions at [https://github.com/SanderMertens/flecs/releases]"
read -p "   > input flecs version (e.g. 3.1.3): " version
source bash/flecs/remove_flecs.sh
download_flecs_source $version
echo "  > remember to build flecs"
echo "      + make build/libflecs.a"