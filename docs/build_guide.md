How-To Building
-----

    The one true guide on how to build zoxel

[Back](../readme.md)

-----

## Welcome

    Download the code & use make commands to build it

    Cross-platform Building (Linux, Windows, Android, Web, IOS*)

    Depends on Flecs, SDL2 & OpenGL 3.0 ES

As a player of our voxel-based RPG, you will have the ability to build and mod to your heart's content. Our game features powerful building mechanics that allow you to create and destroy structures using voxels, giving you the freedom to design and shape your own environments. And with modding support, you can take your creativity even further by creating your own custom content and gameplay mechanics. Whether you want to build a towering fortress, a sprawling city, or something entirely different, the sky's the limit. So why not give building and modding a try and see what you can create? The possibilities are endless!

### Dependencies

I am using these libraries due to their light weight and power -unlimited power-

- [Flecs](https://github.com/SanderMertens/flecs) Fast and lightweight Entity Component System

- [SDL2](https://www.libsdl.org/index.php) Simple DirectMedia Layer (zlib)

- [OpenGL](https://www.khronos.org/opengles/) OpenGL 3.0 ES

In the future I may support Vulkan, for multi threading powers and performance gains.

## The True Way

A quick reference to make commands. Make sure to install flecs first before building zoxel.

```
make help               # if you are feeling lost
```
> download zoxel project source
```
curl -L https://github.com/deus369/zoxel/tarball/master | tar xz && mv deus369-zoxel-* zoxel 
```
> or get the project git repo
```
git clone https://codeberg.org/deus/zoxel
```
> install required libraries
```
sudo apt-get install make               # you need these to build 
make install-required                   # installs required libraries
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
> android
```
make install-android-sdk    # installs android sdk, ndk for android builds
make android                # builds an android apk and pushes it to device (uses gradle)
```