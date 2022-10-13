# Zoxel Makefile!

# ends up close to this but with optimizations
# cc -std=c99 -o zoxel src/Imports/Flecs/flecs.c src/main.c -lGL -lSDL2 -lSDL2_image; valgrind --track-origins=true ./zoxel;

# ended up as
# cc -std=c99 -fPIC -g -o zoxel src/Imports/Flecs/flecs.c src/main.c -lGL -lSDL2 -lSDL2_image -O3 -flto -D NDEBUG

# Memory Testing with valgrind ./zoxel

# \todo Compile flecs first as a .o. Reduce flecs addons into a light weight version.
# \todo Each module will have a seperate Makefile. These will compile a .o file. They will link to the previous .o files.

# Declare compiler tools and flags
CC = cc
CFLAGS =
CFLAGS += -std=c99
CFLAGS += -fPIC
CFLAGS += -g
# Add libraries
LDLIBS = -lGL
LDLIBS += -lSDL2
LDLIBS += -lSDL2_image
# Compiler Optimizations
LDLIBS += -O3
LDLIBS += -flto
# Removes Debug Messages
LDLIBS += -D NDEBUG

# SRCS defines all the files that will be used in the game.
SRCS = 
SRCS += src/Imports/Flecs/flecs.c 
SRCS += src/Imports/Flecs/flecs.h
SRCS += src/main.c
# Imports
SRCS += src/Imports/SDL/SDLUtil.c
SRCS += src/Imports/Flecs/FlecsUtil.c
SRCS += src/Imports/Imports.h
# Players
SRCS += src/Core/Players/Players.h
SRCS += src/Core/Players/Systems/BobSpawnSystem.c
SRCS += src/Core/Players/Systems/BobMoveSystem.c
# Rendering
SRCS += src/Core/Rendering/Rendering.h
SRCS += src/Core/Rendering/Core/RenderingCore.h

# OBJS defines all the files used to compile Zoxel.
OBJS = 
OBJS += src/Imports/Flecs/flecs.c
OBJS += src/main.c

SHDS =
SRCS += src/Shaders/BasicRender2D.vert
SRCS += src/Shaders/BasicRender2D.frag

#all make recursive calls
# sub-make:
#     make -C src/Core/Rendering/MakeRendering

# blob:
#     .incbin $(SHDS)

zoxel: $(SRCS)
	$(CC) $(CFLAGS) $(SHDS) -o $@ $(OBJS) $(LDLIBS)


# Helper target that cleans up build artifacts
# .PHONY: clean

# clean:
#     rm -rf *.o zoxel
	
# rm -fr zoxel zoxel.exe src/*.o

# Default rule for compiling .c files to .o object files
# .SUFFIXES: .c .o
# .c.o:
# 	$(CFLAGS) -c -o $@ $<