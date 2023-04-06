#/bin/bash
# new script that creates a system
#   first pick a module under the zoxel project
#   next name the new system
#   add any components with spaces between or leave blank
#   script will create a new c file with these things in it
#   script will print the lines to add to the module file, including the zoxel_system line and include file

source bash/zoxel/find_modules.sh
source bash/zoxel/systems_util.sh

# todo: check if system already exists
# todo: add lines to module define automatically

selected_module=$(find_module_names ${module_names[@]})
selected_module_filename=$(find_module_path $selected_module)
echo "   > module [$selected_module] selected"
echo "      + at path [$selected_module_filename]"

systems_dir=$(get_system_directory $selected_module_filename)
# echo "      + with systems directory [$systems_dir]"
print_systems $systems_dir

read -p "   > create a new system name: " system_name
if [[ $system_name == "" ]]; then
    echo "  - invalid system name [$system_name]"
    exit
fi
# Prompt user for a list of component names
read -p "   > create input components (separated by spaces): " component_names_input
read -p "   > create output components (separated by spaces): " output_component_names_input

# === process system name ===

# check if system_name is in camel case and separate the words
if [[ "$system_name" =~ [a-z][A-Z] ]]; then
    echo "  + camel case detected in system name"
    system_name=$(echo "$system_name" | sed 's/\([a-z]\)\([A-Z]\)/\1 \2/g; s/\([A-Z]\+\)\([A-Z][a-z]\)/\1 \2/g')
fi
if [[ $system_name == *"_"* ]]; then
    echo "  + underscores detected in system name"
    system_name=$(echo "$system_name" | sed 's/_/ /g')
fi
if [[ ! "$system_name" =~ [Ss][Yy][Ss][Tt][Ee][Mm] ]]; then
    system_name="${system_name} System"
    echo "system added to name: $system_name"
fi
# remove spaces and camel case the name
system_name_lower=$(echo "$system_name" | tr '[:upper:]' '[:lower:]')
system_name_snake=$(echo "$system_name_lower" | sed 's/ /_/g')
system_name_camel=$(echo "$system_name_snake" | sed 's/_\([a-z]\)/\U\1/g;s/\b[a-z]/\U&/g')
lower_case_with_underscores=$(echo "$system_name" | tr '[:upper:]' '[:lower:]' | sed 's/ /_/g')

echo "  > system name [$system_name]"
echo "      - creating a system of name [$system_name_camel]"
echo "      - creating system file [$lower_case_with_underscores.c]"

# process component names
component_names=($component_names_input)
output_component_names=($output_component_names_input)
echo "  > input components:"
for i in "${!component_names[@]}"; do
    component_name=${component_names[$i]}
    # convert first letter to uppercase
    component_name="$(tr '[:lower:]' '[:upper:]' <<< ${component_name:0:1})${component_name:1}"
    component_names[$i]=$component_name
    echo "      + [in] [$component_name]"
done
echo "  > output components:"
for i in "${!output_component_names[@]}"; do
    component_name=${output_component_names[$i]}
    component_name="$(tr '[:lower:]' '[:upper:]' <<< ${component_name:0:1})${component_name:1}"
    output_component_names[$i]=$component_name
    echo "      + [out] [$component_name]"
done

# confirm creation of system directory
create_systems_directory "$systems_dir"

# === create a template system file ===

system_filepath="$systems_dir/$lower_case_with_underscores.c"
echo "  > creating new system file [$system_filepath]"
touch $system_filepath
echo "void $system_name_camel(ecs_iter_t *it) {" >> "$system_filepath"

# add the component lists
i=1
for component_name in "${component_names[@]}"; do
    list_name="$(tr '[:upper:]' '[:lower:]' <<< ${component_name:0:1})${component_name:1}s"
    echo "    const $component_name *$list_name = ecs_field(it, $component_name, $i);" >> "$system_filepath"
    i=$(($i + 1))
done
for component_name in "${output_component_names[@]}"; do
    list_name="$(tr '[:upper:]' '[:lower:]' <<< ${component_name:0:1})${component_name:1}s"
    echo "    $component_name *$list_name = ecs_field(it, $component_name, $i);" >> "$system_filepath"
    i=$(($i + 1))
done

echo "    for (int i = 0; i < it->count; i++) {" >> "$system_filepath"

# add the component variables
for component_name in "${component_names[@]}"; do
    list_name="$(tr '[:upper:]' '[:lower:]' <<< ${component_name:0:1})${component_name:1}s"
    variable_name="$(tr '[:upper:]' '[:lower:]' <<< ${component_name:0:1})${component_name:1}"
    echo "          const $component_name *$variable_name = &$list_name[i];" >> "$system_filepath"
done
for component_name in "${output_component_names[@]}"; do
    list_name="$(tr '[:upper:]' '[:lower:]' <<< ${component_name:0:1})${component_name:1}s"
    variable_name="$(tr '[:upper:]' '[:lower:]' <<< ${component_name:0:1})${component_name:1}"
    echo "          $component_name *$variable_name = &$list_name[i];" >> "$system_filepath"
done

echo "          // add your logic here" >> "$system_filepath"
echo "    }" >> "$system_filepath"
echo "}" >> "$system_filepath"
echo "zoxel_declare_system($system_name_camel)" >> "$system_filepath"

# todo: choose a pipeline EcsOnUpdate, etc
# todo: add these automatically to a module define file [selected_module_filename]
input_component_names_string=$(printf ", [in] %s" "${component_names[@]}")
output_component_names_string=$(printf ", [out] %s" "${output_component_names[@]}")
system_include_line="#include \"systems/$lower_case_with_underscores.c\""
system_define_line="zoxel_system($system_name_camel, EcsOnUpdate$input_component_names_string$output_component_names_string)"

echo " -=== === === === === === === ===-"
echo "  > update your module define [$selected_module_filename] with:"
echo ""
echo "  > system includes:"
echo "      $system_include_line"
echo ""
echo "  > system defines:"
echo "      $system_define_line"
echo ""
echo " === system creation complete ==="
echo " -=== === === === === === === ===-"

# todo: inside module define look for comments to trigger adding at end of lists
# todo: find // zoxel_system_includes and // zoxel_system_defines
# zoxel_system(ProjectionMatrixSystem, EcsOnUpdate, [in] input_components, [out] output_components)
# now add include statements to the module file
# also add a zoxel_system call between begin and end module lines