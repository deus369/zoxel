#!/bin/bash
# open this in wsl - then type in:
# cd /mnt/c/Users/deus/projects/zoxel && make convert-music && make resources
project_directory="/mnt/c/Users/deus/projects/zoxel"
cd $project_directory
echo " > converting music"
echo " > building converter"
gcc -std=c99 $project_directory/src/inner_core/musics/convert/midi.c -o build/midi_converter `pkg-config --cflags --libs glib-2.0` -lm -lsmf
echo " > finished building"
echo " > converting raw/midis/song1.mid"
./build/midi_converter raw/midis/songa.mid
echo " > finished all midi conversion"
