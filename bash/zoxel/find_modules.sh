#!/bin/bash

# Initialize an empty array to hold the module files

# Loop through all .c files in the directory
find_module_filepaths() {
    local search_directory=$1
    echo "  > finding modules in $search_directory" >&2
    module_files=()
    # find $search_directory -name "*.c" | while read file; do
    while read -r file; do
        # echo "  > checking file: $file"
        # checks if the file has zoxel_begin_module at the beginning of any line
        if grep -q "^zoxel_begin_module" "$file"; then
            # echo "    + module file [$file]" >&2
            # echo "  size is ${#module_files[@]}" >&2
            module_files+=("$file")
        fi
    done < <(find "$search_directory" -name "*.c")
    # echo "  + module_files found [${#module_files[@]}]" >&2
    echo "${module_files[@]}"
}

find_module_names() {
    local module_files=("$@")
    local module_names=()
    # echo "  > extracting module names with [${#module_files[@]}] files" >&2
    # Loop through the module files and extract the parameter of zoxel_begin_module
    for module_file in ${module_files[@]}; do
        # Get the parameter of zoxel_begin_module(Apps)
        module_name=$(grep "^zoxel_begin_module" "$module_file" | sed -n 's/^zoxel_begin_module(\([^)]*\)).*$/\1/p')
        module_names+=("$module_name")
        # Print the filename and parameter of the module
        # echo "    + module [$module_name]" >&2
    done
    echo "${module_names[@]}"
}

# echo " === Zoxel Modules [${#module_names[@]}] ==="
# i=0
# for module_file in ${module_files[@]}; do
#     module_name=${module_names[i]}
#     i=$(($i + 1))
#     echo "    + module [$module_name] at [$module_file]"
# done

module_files=$(find_module_filepaths src)

# Check if any module files were found
if [ ${#module_files[@]} -eq 0 ]; then
    echo "  - no module files found"
    exit 0
fi

module_names=($(find_module_names "${module_files[@]}"))

find_module_names() {
    local module_names=("$@")
    echo "  > modules found [${#module_names[@]}]" >&2
    echo " === select a module ===" >&2
    selected_module=""
    select module_name in "${module_names[@]}"; do
        if [[ -n $module_name ]]; then
            selected_module=$module_name
            break
        else
            echo "Invalid selection. Please try again." >&2
        fi
    done
    echo $selected_module
}

find_module_path() {
    local selected_module=$1
    selected_module_filename=""
    i=0
    for module_file in ${module_files[@]}; do
        module_name=${module_names[i]}
        # echo "    + module [$module_name] at [$module_file]" >&2
        if [[ ${module_names[$i]} == $selected_module ]]; then
            selected_module_filename=$module_file
            break
        fi
        i=$(($i + 1))
    done
    echo $selected_module_filename
}