How-To Building
-----

    A quick guide on how I build Zoxel.

[Make](https://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html)

[Back](../../readme.md)

-----

## Building

### Linux

This is for Debian based Linux systems.

Linux [Native]
```
# installls required library
sudo apt install make libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev


# builds `zoxel` binary
make
```

### Extra

```
# Parallel Make (4 is the number of cores)
make -j4

# Use this to use whatever cores your system has
make -j$(nproc)

# Make Dev Build
make -f MakefileDev

# Run Dev Build
./zoxel-dev
```

Use valgrind for debugging memory / stack tracing
```
#install valgrind
sudo apt-get install valgrind

# use valgrind with a binary build
valgrind ./zoxel-dev
```

Download
```
# go to home directory
cd ~

# install git (if required)
sudo apt-get install git

# clone with git
git clone https://codeberg.org/deus/zoxel

# go to zoxel directory for building
cd zoxel
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

Next go to the android web scripts folder

```
cd ~/zoxel/bash/web
```

Now run either of the below to build and/or run
```
sh build-run-web.sh
sh build-web.sh
sh run-web.sh
```

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