#!/bin/bash

# run flecs tests

cd ~/zoxel

test_script=bash/testing/run_flecs_test.sh

echo "---------------------"
echo "--- Testing FLECS ---"

sh $test_script array_access_multi_thread

sh$test_script bulk_spawn

sh $test_script ecs_get_mut

sh $test_script tags_and_modules

sh $test_script spawn_component

sh $test_script prefab_inheritance

echo "--- Ended Testing FLECS ---"
echo "---------------------"

sleep 30