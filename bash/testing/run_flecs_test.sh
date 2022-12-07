#!/bin/bash

# run flecs test
cd ~/zoxel

if [ ! $# -eq 1 ];
then
  echo "$0: Wrong arguments. Give one argument as flecs test name."
  exit 1
else
  # echo "We got some argument(s)"
  echo "======================================="
  test_file_name=$1
  echo "=== Testing [$test_file_name] ===\n"
  # echo "Number of arguments.: $#"
  # echo "List of arguments...: $@"
  # echo "Arg #1..............: $1"
  cc -std=c99 -D_DEFAULT_SOURCE -o tests/builds/$test_file_name include/flecs.c tests/flecs/$test_file_name.c
  ./tests/builds/$test_file_name
  echo "\n=== Ended Test [$test_file_name] ==="
  echo "======================================="
fi