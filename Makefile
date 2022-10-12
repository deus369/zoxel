# Zoxel Makefile!

# ends up close to this but with optimizations
# cc -std=c99 -o zoxel src/Imports/Flecs/flecs.c src/main.c -lGL -lSDL2 -lSDL2_image; valgrind --track-origins=true ./zoxel;

# Declare compiler tools and flags
CC      = cc
CFLAGS  = -std=c99
CFLAGS += -fPIC
CFLAGS += -g
LDFLAGS =
# Add libraries
LDLIBS = -lGL
LDLIBS += -lSDL2
LDLIBS += -lSDL2_image
# Compiler Optimizations
LDLIBS += -O3
LDLIBS += -flto
# Removes Debug Messages
LDLIBS += -D NDEBUG
# main files
SRCS = src/Imports/Flecs/flecs.c src/Imports/Flecs/flecs.h
OBJS = src/Imports/Flecs/flecs.c
SRCS += src/main.c
OBJS += src/main.c
# Memory Testing with valgrind ./zoxel

# Build the main executable 
zoxel: $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Helper target that cleans up build artifacts
.PHONY: clean
clean:
	rm -fr zoxel zoxel.exe src/*.o

# Default rule for compiling .c files to .o object files
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<