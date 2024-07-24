#!/bin/bash
# copies SDL2 and SDL_image src, include and Application into android project
source bash/android/gradle_pathing.sh
start_gradle_build
source bash/util/verbose_echo.sh
# sdl - base
# sdl_directory=$HOME/SDL/SDL2
sdl2_1=$sdl_directory/src
sdl2_2=$sdl_directory/include
sdl2_3=$sdl_directory/Android.mk
sdl2_image_directory_src=$sdl_image_directory/src
sdl2_image_directory_include=$sdl_image_directory/include
sdl2_mixer_directory_src=$sdl_mixer_directory/src
sdl2_mixer_directory_include=$sdl_mixer_directory/include
# destination - where to copy to
destination_directory=$android_directory/app/jni # /src
destination_directory1=$destination_directory/SDL2
destination_directory2=$destination_directory/SDL2_image
destination_directory3=$destination_directory/SDL2_mixer

# first remove source files from new directory

echo "=> copying android sdl"
if [ -d $destination_directory1 ]; then
    echo_2 " > removing dir [$destination_directory1]"
    rm -R $destination_directory1
fi
echo_2 " > copying sdl for android [$sdl_directory]"
echo_2 "  > making directory 1 [$destination_directory1]"
mkdir $destination_directory1
echo_2 "  > copying [$sdl_directory] to [$destination_directory1]"
cp -R $sdl2_1 $destination_directory1
cp -R $sdl2_2 $destination_directory1
cp $sdl2_3 $destination_directory1

if [ -d $destination_directory2 ]; then
    echo_2 " > removing dir [$destination_directory2]"
    rm -R $destination_directory2
fi
if [ "$is_sdl_image" = true ]; then
    echo_2 " > copying sdl_image for android [$sdl_image_directory]"
    echo_2 "  > making directory 2 [$destination_directory2]"
    mkdir $destination_directory2
    echo_2 "  > copying [$sdl_image_directory] to [$destination_directory2]"
    cp $sdl_image_directory/* $destination_directory2 # added -R
    echo_2 "  > copying [$sdl2_image_directory_src] to [$destination_directory2]"
    cp -R $sdl2_image_directory_src $destination_directory2
    echo_2 "  > copying [$sdl2_image_directory_include] to [$destination_directory2]"
    cp -R $sdl2_image_directory_include $destination_directory2
else
    echo_2 " > sdl_image is disabled for android build"
fi

if [ -d $destination_directory3 ]; then
    echo_2 " > removing dir [$destination_directory3]"
    rm -R $destination_directory3
fi
if [ "$is_sdl_mixer" = true ]; then
    echo_2 " > copying sdl_mixer for android [$sdl_mixer_directory]"
    echo_2 "  > making directory 3 [$destination_directory3]"
    mkdir $destination_directory3
    echo_2 "  > copying [$sdl_mixer_directory] to [$destination_directory3]"
    cp $sdl_mixer_directory/* $destination_directory3
    # cp -R $sdl_mixer_directory $destination_directory3 # added -R
    echo_2 "  > copying [$sdl2_mixer_directory_src] to [$destination_directory3]"
    cp -R $sdl2_mixer_directory_src $destination_directory3
    echo_2 "  > copying [$sdl2_mixer_directory_include] to [$destination_directory3]"
    cp -R $sdl2_mixer_directory_include $destination_directory3
else
    echo_2 " > sdl_mixer is disabled for android build"
fi

end_gradle_build
