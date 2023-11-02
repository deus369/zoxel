#!/bin/bash

echo "> checking dev packages"

source bash/util/package_util.sh

install_first_library "gdb"

install_first_library "valgrind"
