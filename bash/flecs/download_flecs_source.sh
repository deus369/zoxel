#!/bin/bash
# this is updated to the latest tested version of flecs
flecs_version="$1"
echo "> updating flecs_version: $flecs_version"
source bash/flecs/flecs_util.sh
download_flecs_source "$flecs_version"
source bash/flecs/post_download_edits.sh
echo "+ downloaded flecs"