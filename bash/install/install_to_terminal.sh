#!/bin/bash

# this as zoxel to terminal
zoxel_run_bash=/etc/profile.d/zoxel.sh
# Check if /usr/games/zoxel is in the PATH
if [[ ":$PATH:" != *":$zoxel_install_directory:"* ]]; then
    # If it's not in the PATH, add it to the end
    echo "  + adding [$zoxel_install_directory] to PATH"
    # export PATH="$PATH:$zoxel_install_directory"
    sudo touch $zoxel_run_bash
    echo "#!/bin/bash" | sudo tee $zoxel_run_bash
    echo "export PATH=\$PATH:$zoxel_install_directory" | sudo tee -a $zoxel_run_bash
    sudo chmod +x $zoxel_run_bash
    source $zoxel_run_bash
else
    echo "  > [$zoxel_install_directory] found in PATH"
fi