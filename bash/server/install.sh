#!/bin/bash
SERVICE_NAME="zoxel.service"
SCRIPT_PATH="/root/zoxel/bash/server/run.sh"
USER="root"  # Change this to your desired user
GROUP="root"  # Change this to your desired group

cat <<EOF | sudo tee /etc/systemd/system/$SERVICE_NAME > /dev/null
[Unit]
Description=Zoxel Server
After=network.target

[Service]
Type=simple
ExecStart=/bin/bash $SCRIPT_PATH
Restart=always
User=$USER
Group=$GROUP
Environment=PATH=/usr/bin:/usr/local/bin:/bin

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd to apply changes
echo "Reloading systemd daemon..."
sudo systemctl daemon-reload

# Enable the service to start on boot
echo "Enabling the service to start on boot..."
sudo systemctl enable $SERVICE_NAME

# Start the service immediately
echo "Starting the service..."
sudo systemctl start $SERVICE_NAME

# Check the service status
echo "Checking service status..."
sudo systemctl status $SERVICE_NAME

echo "Installation completed successfully!"
