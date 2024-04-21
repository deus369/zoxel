#!/bin/bash

# Set the download URL for SDL2
sdl_url="https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-devel-2.30.2-VC.zip"
sdl_zip="build/sdl.zip"
sdl_source="build/sdl/SDL2-2.30.2" # SDL2-2.0.14"
sdl_path="build/sdl"
sdl_dest="build/sdl"

sdl_image_url="https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip"
sdl_image_zip="build/sdl_image.zip"
sdl_image_source="build/sdl_image/SDL2_image-2.8.2" # 2.0.5"
sdl_image_path="build/sdl_image"
sdl_image_dest="build/sdl_image"

sdl_mixer_url="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip"
sdl_mixer_zip="build/sdl_mixer.zip"
sdl_mixer_source="build/sdl_mixer/SDL2_mixer-2.8.0" # 2.0.4"
sdl_mixer_path="build/sdl_mixer"
sdl_mixer_dest="build/sdl_mixer"

glew_url="https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip"
# Set the directory to extract SDL2 to
glew_zip="build/glew.zip"
glew_source="build/glew/glew-2.2.0"
glew_path="build/glew"
glew_dest="build/glew"

# Create the directory if it doesn't exist
rm -r "$sdl_path"
rm -r "$sdl_image_path"
rm -r "$sdl_mixer_path"
rm -r "$glew_path"

mkdir -p "$sdl_path"
mkdir -p "$sdl_image_path"
mkdir -p "$sdl_mixer_path"
mkdir -p "$glew_path"

# Download SDL2 zip file
wget -O "$sdl_zip" "$sdl_url"
wget -O "$sdl_image_zip" "$sdl_image_url"
wget -O "$sdl_mixer_zip" "$sdl_mixer_url"
wget -O "$glew_zip" "$glew_url"

# Extract SDL2 zip file to the C drive
unzip -q "$sdl_zip" -d "$sdl_path"
unzip -q "$sdl_image_zip" -d "$sdl_image_path"
unzip -q "$sdl_mixer_zip" -d "$sdl_mixer_path"
unzip -q "$glew_zip" -d "$glew_path"

# Clean up temporary files
rm "$sdl_zip"
rm "$sdl_image_zip"
rm "$sdl_mixer_zip"
rm "$glew_zip"


# remove folder build/glew/glew-2.2.0
mv "$glew_source"/* "$glew_dest"
rmdir "$glew_source"

# remove folder build/glew/include/GL
glew_source2="build/glew/include/GL"
glew_dest2="build/glew/include"
mv "$glew_source2"/* "$glew_dest2"
rmdir "$glew_source2"

# remove folder build/sdl/SDL2-2.0.14
mv "$sdl_source"/* "$sdl_dest"
rmdir "$sdl_source"

# remove folder build/sdl/SDL2-2.0.14
mv "$sdl_image_source"/* "$sdl_image_dest"
rmdir "$sdl_image_source"

# remove folder build/sdl/SDL2-2.0.14
mv "$sdl_mixer_source"/* "$sdl_mixer_dest"
rmdir "$sdl_mixer_source"

echo " > sdl has been downloaded into build directory"
