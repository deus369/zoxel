#! /bin/bash
# Call this script after git clone'ing zoxel. Copies config settings.

echo "  > [copying bash/git/config] into [.git/config]"
cp bash/git/config .git/config

# echo "Completed."
# sleep 8