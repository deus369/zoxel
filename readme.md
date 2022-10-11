# Libre Zoxel

Open Source & Cross-platform + Performance is on Mushrooms~

Open-Zoxel is under the GPL license as I want any derivatives to stay open, to protect the end users and keep information free.

Zoxel has a large scope as I have many ideas. It's game design is influenced from Minecraft, Warcraft and LitRPGs/Tabletops.

![Le Old Zoxel](/screenshots/KEyHna.png?raw=false "Le Old Zoxel")

W41sdfh.png
## Why The Change?

Zoxel has been in development a long time (over a decade), over many different engines. It is time for it to set sail again to a custom one, using FLECS for performance!

This was not an easy decision. Gotta go fast! Flecs has offered me a way out of the Unity IPO mess, and it offers greater levels of freedom over my development.

There are 120k+ lines on the unity ecs codebase, so it will take some time for things to be ported.

[Itch IO Old Zoxel](https://deus0.itch.io/zoxel) Developed from 2017 with Unitys ECS

## How far along is it?

So far I am fleshing out basic systems while testing out Flecs useage. So far the performance has been promising!

![El Libre Zoxel](/screenshots/W41sdfh.png?raw=false "El Libre Zoxel")

## Dependencies

[SDL2](https://www.libsdl.org/index.php) Simple DirectMedia Layer (zlib)

[Flecs](https://github.com/SanderMertens/flecs) Fast and lightweight Entity Component System

## Building
This project is built using POSIX-compatible [make](https://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html).
For unix-like systems, it can be built natively.

### Linux

Linux (Debian-based) [Native]
```
sudo apt install make libsdl2-dev
make
```

### Windows [todo]

[mingw-w64](http://mingw-w64.org/doku.php) is used to cross-compile the project from a unix-like system.

Linux
```
sudo apt install make wget tar mingw-w64
make -f Makefile.mingw
```


### MacOS [todo]

Linux
```
brew install make sdl2
make -f Makefile.macos
```

MacOS [Native]
```
brew install make wget gnu-tar mingw-w64
make -f Makefile.mingw
```