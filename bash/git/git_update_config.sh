#! /bin/bash
# Call this script after git clone'ing zoxel. Copies config settings.

echo "Copying config file into git folder."
cp config ../../.git/config
echo "Completed."
sleep 8