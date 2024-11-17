#! /bin/bash

# Run this before making zoxel if has no sdl_mixer library
# note: can i run this from a make command, and check library there?

echo Cloning latest sdl mixer library to home
cd ~

if [[ -d SDL ]]; then
	echo SDL exists in home.
else
	echo Adding SDL directory in home
    mkdir SDL
fi
cd SDL

if [[ -d SDL_mixer ]]; then
	echo SDL_mixer already exists. Just updating.
    cd SDL_mixer
    git pull
else
	echo Cloning new SDL_mixer
    git clone https://github.com/libsdl-org/SDL_mixer
    cd SDL_mixer
fi

echo Generating configuration files
sh autogen.sh

echo Making build folder sub directory
mkdir build
cd build

echo Configuring build folder
../configure

echo Making SDL_mixer
make all

# if [[ -d /usr/local/lib/SDL_mixer ]]; then
# 	echo /usr/local/lib/SDL_mixer exists.
# else
# 	echo Adding directory /usr/local/lib/SDL_mixer
#     mkdir /usr/local/lib/SDL_mixer
# fi

echo Installing SDL_mixer
sudo make install

# echo Installed in $LIBDIR
LIBDIR=/usr/local/lib
echo Installed in $LIBDIR

export LD_RUN_PATH=$LIBDIR
# sudo mv /usr/local/lib/libSDL2_mixer.so /usr/local/lib/SDL_mixer/libSDL2_mixer.so
# sudo mv /usr/local/lib/libSDL2_mixer-2.0.so.0 /usr/local/lib/SDL_mixer/libSDL2_mixer-2.0.so.0

# cd ~
# echo Removing install folder SDL_mixer
# rm -r SDL_mixer

echo Finished installing latest sdl mixer library.

sleep 155
