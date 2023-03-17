How-To Building
-----

    The one true guide on how to build Zoxel

[Back](../readme.md)

-----

## Welcome

    Download the code & use make commands to build it

    Cross-platform Building (Linux, Windows, Android, Web, IOS*)

    Depends on Flecs, SDL2 & OpenGL 3.0 ES

As a player of our voxel-based RPG, you will have the ability to build and mod to your heart's content. Our game features powerful building mechanics that allow you to create and destroy structures using voxels, giving you the freedom to design and shape your own environments. And with modding support, you can take your creativity even further by creating your own custom content and gameplay mechanics. Whether you want to build a towering fortress, a sprawling city, or something entirely different, the sky's the limit. So why not give building and modding a try and see what you can create? The possibilities are endless!

## The true way

A quick reference to make commands. Make sure to install flecs first before building zoxel.

```
make help               # if you are feeling lost
```
> install zoxel and required libraries
```
sudo apt-get install git make               # you need these to build 
git clone https://codeberg.org/deus/zoxel   # first get the project
make install-required                       # installs required libraries
```
> install flecs using make > bash commands
```
make install-flecs      # installs flecs v3.0.3 files
make build/libflecs.a   # builds flecs library
```
> for linux or windows
```
make                    # builds a release build
make build/dev          # builds a dev build
make -j$(nproc)         # multithreaded building
```
> linux
```
make install            # installs zoxel
zoxel                   # runs zoxel after installed
```
> web
```
make install-web-sdk    # installs emscripten for web builds
make build/zoxel.html   # build web
make run-web            # run web
```

## Dependencies

I am using these libraries due to their light weight and power -unlimited power-

- [Flecs](https://github.com/SanderMertens/flecs) Fast and lightweight Entity Component System

- [SDL2](https://www.libsdl.org/index.php) Simple DirectMedia Layer (zlib)

- [OpenGL](https://www.khronos.org/opengles/) OpenGL 3.0 ES

I may switch to Glut in the future to reduce build size even more, instead of SDL.

I may also try out Vulkan, for multi threading powers and performance.

## Android [On Linux]

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