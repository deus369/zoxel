#!/bin/bash


# Set the download URL for SDL2
sdl_url="https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-2.30.2.zip"
sdl_zip="build/sdl.zip"
sdl_path="build/linux-sdl"
sdl_source="$sdl_path/SDL2-2.30.2" # SDL2-2.0.14"
sdl_dest=$sdl_path

sdl_image_url="https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.zip"
sdl_image_zip="build/sdl_image.zip"
sdl_image_path="build/linux-sdl_image"
sdl_image_source="$sdl_image_path/SDL2_image-2.8.2" # 2.0.5"
sdl_image_dest=$sdl_image_path

sdl_mixer_url="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.zip"
sdl_mixer_zip="build/sdl_mixer.zip"
sdl_mixer_path="build/linux-sdl_mixer"
sdl_mixer_source="$sdl_mixer_path/SDL2_mixer-2.8.0" # 2.0.4"
sdl_mixer_dest=$sdl_mixer_path

glew_url="https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
# Set the directory to extract SDL2 to
glew_zip="build/glew.zip"
glew_path="build/linux-glew"
glew_source="$glew_path/glew-2.2.0"
glew_dest=$glew_path

# Create the directory if it doesn't exist
# rm -r "$sdl_path"
# rm -r "$sdl_image_path"
# rm -r "$sdl_mixer_path"
# rm -r "$glew_path"
if [ ! -d $sdl_path ]; then
    mkdir -p "$sdl_path"
fi
if [ ! -d $sdl_image_path ]; then
    mkdir -p "$sdl_image_path"
fi
if [ ! -d $sdl_mixer_path ]; then
    mkdir -p "$sdl_mixer_path"
fi
if [ ! -d $glew_path ]; then
    mkdir -p "$glew_path"
fi

# Download SDL2 zip file
wget -O "$sdl_image_zip" "$sdl_image_url"
wget -O "$sdl_mixer_zip" "$sdl_mixer_url"
wget -O "$glew_zip" "$glew_url"

# Extract SDL2 zip file to the C drive
unzip -q "$sdl_image_zip" -d "$sdl_image_path"
unzip -q "$sdl_mixer_zip" -d "$sdl_mixer_path"
unzip -q "$glew_zip" -d "$glew_path"

# Clean up temporary files
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
mv "$sdl_image_source"/* "$sdl_image_dest"
rmdir "$sdl_image_source"

# remove folder build/sdl/SDL2-2.0.14
mv "$sdl_mixer_source"/* "$sdl_mixer_dest"
rmdir "$sdl_mixer_source"

if [ ! -f lib/libGLEW.a ]; then
    if [ ! -f $glew_path/lib/libGLEW.a ]; then
        cd $glew_path
        make
        cd ../.. # return to zoxel
    fi
    cp $glew_path/lib/libGLEW.a lib/libGLEW.a
fi

if [ ! -f lib/libSDL2.la ]; then
    # download sdl2
    wget -O "$sdl_zip" "$sdl_url"
    unzip -q "$sdl_zip" -d
    rm "$sdl_zip"
    # remove folder build/sdl/SDL2-2.0.14"$sdl_path"
    mv "$sdl_source"/* "$sdl_dest"
    rmdir "$sdl_source"
    if [ ! -f $sdl_path/build/libSDL2.la ]; then
        cd $sdl_path
        ./configure
        make
        cd ../..
    fi
    cp $sdl_path/build/libSDL2.la "lib/libSDL2.la"
fi

if [ ! -f "lib/libSDL2_image.la" ]; then
    if [ ! -f $sdl_image_path/libSDL2_image.la ]; then
        cd $sdl_image_path
        ./configure
        make
        cd ../..
    fi
    cp $sdl_image_path/libSDL2_image.la "lib/libSDL2_image.la"
fi

if [ ! -f "lib/libSDL2_mixer.la" ]; then
    if [ ! -f $sdl_mixer_path/build/libSDL2_mixer.la ]; then
        cd $sdl_mixer_path
        ./configure
        make
        cd ../..
    fi
    cp $sdl_mixer_path/build/libSDL2_mixer.la "lib/libSDL2_mixer.la"
fi

echo " > sdl has been downloaded into build directory"
