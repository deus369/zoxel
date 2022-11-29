#! /bin/bash

echo Installing latest sdl mixer library

echo Removing any leftover files
rm master.zip
rm -r SDL_mixer-main

wget github.com/libsdl-org/SDL_mixer/archive/master.zip

echo unzipping
unzip master.zip
rm master.zip

echo building sdl mixer
cd SDL_mixer-main
sh autogen.sh
./configure
make
make install

if [[ $LD_LIBRARY_PATH =~ /usr/local/lib ]]; then
	echo Path [/usr/local/lib] already exists in LD_LIBRARY_PATH
else
	echo Adding Path [/usr/local/lib] to LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
fi

echo Removing install folder SDL_mixer-main
rm -r SDL_mixer-main

echo Finished installing latest sdl mixer library.

sleep 20
