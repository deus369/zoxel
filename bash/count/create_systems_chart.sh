#!/bin/bash
# uses terminal tools: gnuplot & ristretto

is_debug=0
graph_width=1920*1
graph_height=1080*1
graph_name="build/systems_count.png"
data_file="build/bar_data.txt"
sorted_data_file="build/bar_data2.txt"
# Define y-axis range
y_min=0
y_max=16
# margins
edge=32
lmargin=11 #$edge
rmargin=5 #-$edge
tmargin=5 #$edge
bmargin=16 #-$edge
# colors
tickcolor="0xAACCAA"
# font sizes
title_size=24
subtitle_size=18
# Define color ranges
red_threshold=10
blue_threshold_min=5
blue_threshold_max=9
# extra
is_sort=0
# data
total_systems=0

if [ -f $data_file ]; then
    rm $data_file
fi

if [ -f $sorted_data_file ]; then
    rm $sorted_data_file
fi

# Function to generate bar graph data
generate_bar_graph_data() {
    local modules_dir="$1"
    local data_file="$2"
    # Iterate through all module files
    # find "$modules_dir" -type f -name '*.c' -exec grep -H 'zox_begin_module' {} + | while IFS= read -r module_line; do
    while IFS= read -r module_line; do
        local_systems_count=5
        local module_file=$(echo "$module_line" | cut -d: -f1)
        local module_name=$(echo "$module_line" | sed -n 's/.*zox_begin_module(\(.*\)).*/\1/p')
        # Count systems in the systems directory of each module
        local systems_dir=$(dirname "$module_file")/systems
        if [ -d $systems_dir ]; then
            local system_count=$(grep -R 'zox_declare_system' "$systems_dir" | wc -l)
            # Output module name and system count to data file
            if [ $is_debug -eq 1 ]; then
                echo " > module [$module_name] - systems [$system_count]"  # Debug output
            fi
            if [ $system_count != 0 ]; then
                echo "$module_name $system_count" >> "$data_file"
                total_systems=$((total_systems + system_count))
            fi
        else
            if [ $is_debug -eq 1 ]; then
                echo " > module [$module_name] has no systems"
            fi
        fi
    done < <(find "$modules_dir" -type f -name '*.c' -exec grep -H 'zox_begin_module' {} +)
}

# Main script
modules_dir="src"  # Adjust this to your modules directory

# Generate bar graph data
generate_bar_graph_data "$modules_dir" "$data_file"

#sorted_data_file="sorted_$data_file"
# sort -rn -k2 "$data_file" | head -n 3 > "$sorted_data_file"
if [ $is_sort -eq 0 ]; then
    cat "$data_file" > "$sorted_data_file"
else
    sort -rn -k2 "$data_file" > "$sorted_data_file"
fi

# Use gnuplot to plot the data and save it as a PNG image
gnuplot << EOF
set terminal png size $graph_width,$graph_height
set output '$graph_name'
set xlabel 'Modules' font 'Monocraft,$subtitle_size'
set ylabel 'Systems' font 'Monocraft,$subtitle_size'
set title 'Zoxel Systems [$total_systems]' font 'Monocraft,$title_size'
set boxwidth 0.8
set style fill solid
set xtics rotate
unset key

# Set background color to black
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "0x080808" behind

# Set border color to white
set border lc rgb "0xBBBBBB"

# set title
set title textcolor rgb "0x00FF00"
set xlabel textcolor rgb "0x00FF00"
set ylabel textcolor rgb "0x00FF00"

# Set font for bar labels
set xtics font 'Monocraft,12'
set xtics textcolor rgb "$tickcolor"

# Set font for left labels
set ytics font 'Monocraft,12'
set ytics textcolor rgb "$tickcolor"

set lmargin $lmargin
set rmargin $rmargin
set tmargin $tmargin
set bmargin $bmargin

# Set y-axis range
set yrange [$y_min:$y_max]

# Plot data with color ranges
# plot '$sorted_data_file' using 0:2:xtic(1) with boxes
plot '$sorted_data_file' using 0:2:(\$2 >= 10 ? 0x00CC00 : (\$2 >= 5 && \$2 <= 9 ? 0x337733 : 0x002200)):xtic(1) with boxes lc rgb variable

EOF

echo " + saved [$graph_name] with systems [$total_systems]"
ristretto "$graph_name"

