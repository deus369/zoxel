#! /bin/bash

count_lines() {
    local dir=$1
    git ls-files --full-name "$dir" | grep "^$dir/.*\.c$" | xargs wc -l | tail -n 1 | awk '{print $1}'
}

get_module_directories() {
    find src -mindepth 2 -maxdepth 2 -type d | sed 's|src/||'
}

#total_lines=$(count_lines "src")
#echo " > zoxel lines [$total_lines]"
#module_directories=$(get_module_directories)
#echo " > [modules]"
#for module in $module_directories; do
#    module_lines=$(count_lines "src/$module")
#    if [ "$total_lines" -ne 0 ]; then
#        percentage=$(echo "scale=1; ($module_lines * 100 / $total_lines)" | bc)
#        formatted_percentage=$(printf "%.1f" "$percentage")
#    else
#        formatted_percentage="0"
#    fi
#    echo "   + [$module]: $module_lines [$formatted_percentage%]"
#done

print_modules() {
    local sort=$1
    local -a modules_with_counts=()

    module_directories=$(get_module_directories)

    for module in $module_directories; do
        module_lines=$(count_lines "src/$module")
        if [ "$total_lines" -ne 0 ]; then
            percentage=$(echo "scale=2; ($module_lines * 100 / $total_lines)" | bc)
            formatted_percentage=$(printf "%.2f" "$percentage")
        else
            formatted_percentage="0"
        fi
        modules_with_counts+=("$module:$module_lines:$formatted_percentage")
    done

    if [ "$sort" = true ]; then
        IFS=$'\n' sorted_modules=($(sort -t ':' -k2 -nr <<< "${modules_with_counts[*]}"))
    else
        sorted_modules=("${modules_with_counts[@]}")
    fi

    echo " > [modules]"
    for module in "${sorted_modules[@]}"; do
        IFS=':' read -r module_name module_count module_percentage <<< "$module"
        echo "  - [$module_percentage%] : [$module_name] ($module_count)"
    done
}

total_lines=$(count_lines "src")
echo " > zoxel lines [$total_lines]"

# Call the function with sorting option
sort_by_count=true  # Change to false if you do not want sorting
print_modules $sort_by_count
