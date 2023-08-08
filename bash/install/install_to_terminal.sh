#!/bin/bash

# this as zoxel to terminal
zoxel_run_path="$zoxel_install_directory"
echo "  > installing zoxel command to terminal"
echo "      + run path is [$zoxel_run_path]"
echo "      + Path is [$PATH]"
zoxel_run_bash=/etc/profile.d/zoxel.sh
# Check if /usr/games/zoxel is in the PATH
# zoxel_run_path="$zoxel_install_directory/build"
if [[ ":$PATH:" != *":$zoxel_run_path:"* ]]; then
    # If it's not in the PATH, add it to the end
    echo "  + adding [$zoxel_run_path] to PATH"
    # export PATH="$PATH:$zoxel_install_directory"
    sudo touch $zoxel_run_bash
    echo "#!/bin/bash" | sudo tee $zoxel_run_bash
    echo "export PATH=\$PATH:$zoxel_run_path" | sudo tee -a $zoxel_run_bash
    sudo chmod +x $zoxel_run_bash
    export PATH=$PATH:$zoxel_run_path
    echo "  + Path is now [$PATH]"
    # bash $zoxel_run_bash
    # echo "  > bash file is:"
    # cat $zoxel_run_bash
else
    echo "  > [$zoxel_run_path] found in PATH"
fi