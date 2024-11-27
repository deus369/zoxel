# zoxel build guide

    the one true guide on how to build zoxel

[Back](../readme.md)

-----

## build zoxel

    download the code & use make commands to build it
    cross-platform: linux, windows, android & web
    depends on flecs, sdl2 & opengl 3.0 es
    light weight and power -unlimited power-

-----

## the true way

a quick reference to make commands

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
make download-flecs      # installs flecs v3.0.3 files
make flecs               # builds flecs library
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
make install-android-sdk    # installs java, android sdk, ndk for android building
make android-create-key     # create a storekey in ~/.keys directory to use for signing a release build
make android                # builds, installs and runs and android release build
make android-dev            # builds, installs and runs and android dev build
make android-dev-debug      # builds, installs, runs and debugs and android dev build
make android-uninstall      # uninstalls zoxel from device, release and dev will conflict
```
> lost little lambs
```
make help               # if you are feeling lost
```

### why though?

<p>
As a player of our voxel-based RPG, you will have the ability to build and mod to your heart's content. Our game features powerful building mechanics that allow you to create and destroy structures using voxels, giving you the freedom to design and shape your own environments. And with modding support, you can take your creativity even further by creating your own custom content and gameplay mechanics. Whether you want to build a towering fortress, a sprawling city, or something entirely different, the sky's the limit. So why not give building and modding a try and see what you can create? The possibilities are endless!
</p>

<p align="center">
~ one day, i may support vulkan, for performance gains ~
</p>

-----

<p align="center">
  <img width="64" src="../resources/textures/game_icon.png" alt="Zoxel Logo">
</p>

<p align="center">
  [
  <a href="https://github.com/SanderMertens/flecs">flecs</a>
  <a style="margin-left: 10px;"> | </a>
  <a href="https://www.libsdl.org">sdl</a>
  <a style="margin-left: 10px;"> | </a>
  <a href="https://www.khronos.org/opengles">opengl</a>
  ]
</p>
