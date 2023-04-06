#/bin/bash

# remove the filename from the path and add "systems" directory
get_system_directory() {
    local module_filename=$1
    systems_dir="$(dirname "$module_filename")/systems"
    echo $systems_dir
}

print_systems() {
    local systems_dir=$1
    if [[ -d "$systems_dir" ]]; then
        echo "  > current systems in [$systems_dir]" >&2
        for file in "$systems_dir"/*.c; do
            name=$(basename "$file" .c)
            system_name=$(echo "$name" | sed 's/_\([a-z]\)/\U\1/g;s/\b[a-z]/\U&/g')
            echo "      + [$system_name]" >&2
        done
    fi
}

create_systems_directory() {
    local systems_dir=$1
    # Create the systems directory if it doesn't exist
    if [[ ! -d "$systems_dir" ]]; then
        echo "  - systems directory doesn't exist yet" >&2
        read -p "   > would you like to create it? [y/n]: " create_systems_dir >&2
        if [[ $create_systems_dir == "y" ]]; then
            mkdir "$systems_dir"
            echo "  + created directory [$systems_dir]" >&2
        else
            echo "  - exiting script without creating [$systems_dir]" >&2
            exit 1
        fi
    fi
}