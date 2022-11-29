How-To Building
-----

    This project is built using POSIX-compatible Make. For unix-like systems, it can be built natively.

[Make](https://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html)


[Back](../../readme.md)

-----

## Building

### Linux

This is for Debian based Linux systems.

Linux [Native]
```
sudo apt install make libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev

make
```

### Windows [On Linux]

[mingw-w64](http://mingw-w64.org/doku.php) is used to cross-compile the project from a unix-like system.

```
sudo apt install libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev mingw-w64 make tar wget
make -f MakefileToWindows
```

### Extra

Parallel Make (x is the number of cores)
```
make -jx
```

Use dev settings for testing
```
make -B -f MakefileDev; ./zoxel-dev
```

Use valgrind for debugging memory / stack tracing
```
valgrind ./zoxel-dev
```


### Windows [Native] [todo]

### MacOS [On Linux] [todo]

### MacOS [Native] [todo]