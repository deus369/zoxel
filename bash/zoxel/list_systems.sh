#/bin/bash

source bash/zoxel/find_modules.sh
source bash/zoxel/systems_util.sh

selected_module=$(find_module_names ${module_names[@]})
selected_module_filename=$(find_module_path $selected_module)
systems_dir=$(get_system_directory $selected_module_filename)
print_systems $systems_dir