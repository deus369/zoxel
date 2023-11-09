#!/bin/bash
# copies SDL2 and SDL_image src, include and Application into android project
source bash/android/gradle_pathing.sh
start_gradle_build

echo "=> copying android sdl"

# sdl - base
# sdl_directory=$HOME/SDL/SDL2
sdl2_1=$sdl_directory/src
sdl2_2=$sdl_directory/include
sdl2_3=$sdl_directory/Android.mk
# image
# sdl_image_directory=$HOME/SDL/SDL2_image
# mixer
# sdl_mixer_directory=$HOME/SDL/SDL2_mixer
sdl2_mixer_directory_src=$sdl_mixer_directory/src
sdl2_mixer_directory_include=$sdl_mixer_directory/include
# destination - where to copy to
destination_directory=$android_directory/app/jni # /src
destination_directory1=$destination_directory/SDL2
destination_directory2=$destination_directory/SDL2_image
destination_directory3=$destination_directory/SDL2_mixer

# first remove source files from new directory
echo "  > removing old sdl directories"
rm -R $destination_directory1
rm -R $destination_directory2
rm -R $destination_directory3

echo "  > making directory 1 [$destination_directory1]"
mkdir $destination_directory1
echo "  > copying [$sdl_directory] to [$destination_directory1]"
cp -R $sdl2_1 $destination_directory1
cp -R $sdl2_2 $destination_directory1
cp -R $sdl2_3 $destination_directory1

echo "  > making directory 2 [$destination_directory2]"
mkdir $destination_directory2
echo "  > copying [$sdl_image_directory] to [$destination_directory2]"
cp $sdl_image_directory/* $destination_directory2

echo "  > making directory 3 [$destination_directory3]"
mkdir $destination_directory3
echo "  > copying [$sdl_mixer_directory] to [$destination_directory3]"
cp $sdl_mixer_directory/* $destination_directory3
echo "  > copying [$sdl2_mixer_directory_src] to [$destination_directory3]"
cp -R $sdl2_mixer_directory_src $destination_directory3
echo "  > copying [$sdl2_mixer_directory_include] to [$destination_directory3]"
cp -R $sdl2_mixer_directory_include $destination_directory3

end_gradle_build
