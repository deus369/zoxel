#! /bin/bash

echo Checking Pathing for static linking of SDL_mixer

if [[ $LD_LIBRARY_PATH == "" ]]; then
	echo Adding New Path [/usr/local/lib] to LD_LIBRARY_PATH
	export LD_LIBRARY_PATH="/usr/local/lib"
elif [[ $LD_LIBRARY_PATH =~ /usr/local/lib ]]; then
	echo Path [/usr/local/lib] already exists in LD_LIBRARY_PATH
else
	echo Adding Path [/usr/local/lib] to LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
fi

echo Checking Library Path [$LD_LIBRARY_PATH]
