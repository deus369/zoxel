#!/bin/bash

# run our zoxel_web

cd $HOME/zoxel/documents/zoxel_web

source check_local_ip.sh

#sudo cc zoxel_web.c -o zoxel_web && sudo ./zoxel_web
cc zoxel_web.c -o zoxel_web && ./zoxel_web