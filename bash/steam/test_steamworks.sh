#!/bin/sh
# builds test_steamworks

source bash/steam/build_wrapper.sh

test_output="build/test_steamworks"

source bash/steam/build_test_steamworks.sh

# runs it
./$test_output

# achievements
# go to https://partner.steamgames.com/apps/achievements/<game_id>
#   zoxel is 1412400
#   test achievement is Zoxeller

# upload directly here:
# https://partner.steamgames.com/apps/depotuploads/1412400
# make sure to hit commit before publishing changes
# check builds > https://partner.steamgames.com/apps/builds/1412400
# there is a depots includled collumn
