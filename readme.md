# Zoxel
Cross-platform OpenGL using SDL2 & Flecs

## Dependencies
[SDL2](https://www.libsdl.org/index.php) (zlib) - Simple DirectMedia Layer
[Flecs](https://github.com/SanderMertens/flecs) - Flecs

## Building
This project is built using POSIX-compatible [make](https://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html).
For unix-like systems, it can be built natively.

### Linux (Native, Debian-based)
```
sudo apt install make libsdl2-dev
make
```

### macOS (Native)
```
brew install make sdl2
make -f Makefile.macos
```

### Windows (Cross-Compile)
From Linux (Debian-based):
```
sudo apt install make wget tar mingw-w64
make -f Makefile.mingw

[mingw-w64](http://mingw-w64.org/doku.php) is used to cross-compile the project from a unix-like system.
```

From macOS:
```
brew install make wget gnu-tar mingw-w64
make -f Makefile.mingw
```
