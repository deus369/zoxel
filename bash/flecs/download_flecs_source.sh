#!/bin/bash

# this is updated to the latest tested version of flecs

source bash/flecs/flecs_util.sh
# download_flecs_source "3.2.11" # this version is bugged possibly
download_flecs_source "3.2.6"
source bash/flecs/post_download_edits.sh
