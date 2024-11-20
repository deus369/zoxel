#!/bin/bash
SERVICE_NAME="zoxel.service"
systemd_filepath="/etc/systemd/system/$SERVICE_NAME"
echo " - removing [$systemd_filepath]"
sleep 12
sudo rm $systemd_filepath
sudo systemctl daemon-reload
echo " > finished removing [$SERVICE_NAME]"
