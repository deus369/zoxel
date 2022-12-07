How-To Building
-----

    A quick guide on how I build Zoxel.

[Return Home](../../readme.md)

-----

## Building

### Download

```
# go to home directory
cd ~

# install git (if required)
sudo apt-get install git

# clone with git
git clone https://codeberg.org/deus/zoxel

# go to zoxel directory for building
cd zoxel

# for a list of commands
make help
```

### Linux

This is for Debian based Linux systems.

Linux [Native]
```
# installls required library
sudo apt install make libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev

# builds zoxel binary
#   j flag = processor core count
make -j$(nproc)

# installs zoxel binary, shortcut and resources
make install

# removes those installed files
make uninstall
```

### Dev Mode

Make Zoxel Dev

```
# Make Dev Build
make zoxel-dev

# Run Dev Build
make run-dev
```

Use valgrind for debugging memory / stack tracing
```
#install valgrind
sudo apt-get install valgrind

# use valgrind with a binary build
make run-dev-debug
```

### Windows [On Linux]

[mingw-w64](http://mingw-w64.org/doku.php) is used to cross-compile the project from a unix-like system.

```
sudo apt install libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev mingw-w64 make tar wget
make -f MakefileToWindows
```

### Web [On Linux]

This is to compile zoxel with emscripten as web asm

First install emscripten sdk using their guide https://emscripten.org/docs/getting_started/downloads.html

This should put emsdk inside your home directory

```
# uses a bash to install emcc for building web
make install-web-builder

# This loads emsdk environment variables
#   [must run before using other commands]
source ~/emsdk/emsdk_env.sh

# build zoxel web build
source ~/emsdk/emsdk_env.sh; make -j$(nproc) web/zoxel.js

# run zoxel web build
source ~/emsdk/emsdk_env.sh; make run-web
```

Note: Javascript must be enabled to run web build

### Android [On Linux]

This is to compile zoxel as an apk

First install ndk in $HOME/android/ndk

Next install android-sdk in /usr/lib/android-sdk

Third, install SDL into $HOME/SDL/ under sub directories:
    SDL2, SDL2_image, SDL2_mixer

Go to the android bash scripts folder
```
cd ~/zoxel/bash/android
```

Now run the installer which will copy all files needed, including zoxel source code and settings.
```
sh android_total_install.sh
```

To run, connect an android device with the right privlages and run the bash below
```
sh gradle_install_debug.sh
```

### MacOS [On Linux] [todo]

### IOS [On Linux] [todo]

### Windows [Native] [todo]

[Make](https://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html)