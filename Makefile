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
SRCS += Source/Imports/Flecs/flecs.c 
SRCS += Source/Imports/Flecs/flecs.h
SRCS += Source/main.c
# Imports
SRCS += Source/Imports/SDL/SDLUtil.c
SRCS += Source/Imports/Flecs/FlecsUtil.c
SRCS += Source/Imports/Imports.h
# Players
SRCS += Source/Core/Players/Players.h
SRCS += Source/Core/Players/Systems/BobSpawnSystem.c
SRCS += Source/Core/Players/Systems/BobMoveSystem.c
# Rendering
SRCS += Source/Core/Rendering/Rendering.h
SRCS += Source/Core/Rendering/Core/RenderingCore.h

# OBJS defines all the files used to compile Zoxel.
OBJS = 
OBJS += Source/Imports/Flecs/flecs.c
OBJS += Source/main.c

SHDS =
SRCS += Resources/Shaders/BasicRender2D.vert
SRCS += Resources/Shaders/BasicRender2D.frag

zoxel: $(SRCS)
	$(CC) $(CFLAGS) $(SHDS) -o $@ $(OBJS) $(LDLIBS)