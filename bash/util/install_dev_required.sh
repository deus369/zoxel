#!/bin/bash

echo "> checking dev packages"

source bash/util/package_util.sh

echo "> installing gdb"
install_first_library "gdb"

echo "> installing valgrind"
install_first_library "valgrind"
