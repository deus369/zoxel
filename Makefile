# Zoxel Makefile!

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
LDLIBS += -lm	# for math.h
# Compiler Optimizations & Debug
LDLIBS += -O3
LDLIBS += -flto
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
SRCS += Resources/Shaders/BasicRender2D.vert
SRCS += Resources/Shaders/BasicRender2D.frag

zoxel: $(SRCS)
	$(CC) $(CFLAGS) $(SHDS) -o $@ $(OBJS) $(LDLIBS)