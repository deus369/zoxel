#!/bin/bash

# Function to process each .c file and count occurrences
process_c_file() {
    local file="$1"

    # Count occurrences of 'zox_declare_system'
    local system_count=$(grep -o 'zox_declare_system' "$file" | wc -l)

    # Count occurrences of 'zox_prefab' and 'zox_prefab_child'
    local prefab_count=$(grep -oE 'zox_prefab(z_child)?' "$file" | wc -l)

    # Add counts to total
    total_systems=$((total_systems + system_count))
    total_prefabs=$((total_prefabs + prefab_count))
}

# Main function to iterate through .c files in src directory and subdirectories
main() {
    local src_dir="src"

    # Initialize counts
    total_systems=0
    total_prefabs=0

    # Find all .c files in src directory and subdirectories
    while IFS= read -r -d '' file; do
        process_c_file "$file"
    done < <(find "$src_dir" -type f -name '*.c' -print0)

    echo "Total systems: $total_systems"
    echo "Total prefabs: $total_prefabs"
}

main
