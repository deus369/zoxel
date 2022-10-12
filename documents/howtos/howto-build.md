How-To Building
-----

[Back](../../readme.md)

-----

## Building
This project is built using POSIX-compatible [make](https://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html).
For unix-like systems, it can be built natively.

### Linux

Linux (Debian-based) [Native]
```
sudo apt install make libsdl2-dev libsdl2-image-dev
make
```

Parallel Make (x is the number of cores)
```
make -jx
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