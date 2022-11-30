#! /bin/bash

echo Cloning latest sdl mixer library to home
cd ~
git clone https://github.com/libsdl-org/SDL_mixer

echo Generating configuration files
cd SDL_mixer
sh autogen.sh

echo Making build folder sub directory
mkdir build
cd build

echo Configuring build folder
../configure

echo Making SDL_mixer
make

echo Installing SDL_mixer
make install

echo Checking Pathing for static linking of SDL_mixer
if [[ $LD_LIBRARY_PATH =~ /usr/local/lib ]]; then
	echo Path [/usr/local/lib] already exists in LD_LIBRARY_PATH
else
	echo Adding Path [/usr/local/lib] to LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
fi

# cd ~
# echo Removing install folder SDL_mixer
# rm -r SDL_mixer

echo Finished installing latest sdl mixer library.

# sleep 20
