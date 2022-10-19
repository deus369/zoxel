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
# LDLIBS += -SDL2_IMAGE_FORMATS='["png"]'
LDLIBS += -lm	# for math.h
LDLIBS += -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
# Compiler Optimizations & Debug
LDLIBS += -O3
LDLIBS += -D NDEBUG
# this causes errors
LDLIBS += -flto=auto	# fuse linker plugin
# LDLIBS += -flto-partition=none
# https://stackoverflow.com/questions/66350310/link-time-optimizations-in-cuda-11-what-are-they-and-how-to-use-them
# LDLIBS += -dlto	# Dynamic Link-Time Optimization

# SRCS defines all the files that will be used in the game.
SRCS = 
SRCS += Source/Imports/Flecs/flecs.c 
SRCS += Source/Imports/Flecs/flecs.h
SRCS += Source/main.c
# Imports
SRCS += Source/Core/App/Util/SDLUtil.c
SRCS += Source/Core/App/Util/FlecsUtil.c
# Gameplay
# Characters2D
SRCS += Source/Gameplay/Characters2D/Characters2D.c
SRCS += Source/Gameplay/Characters2D/Systems/BobSpawnSystem.c
# Players
SRCS += Source/Space/Players/Players.c
SRCS += Source/Space/Players/Systems/Player2DMoveSystem.c
# Rendering
SRCS += Source/Core/Rendering/Rendering.c
SRCS += Source/Core/Rendering/Core/RenderingCore.c

# OBJS defines all the files used to compile Zoxel.
OBJS = 
OBJS += Source/Imports/Flecs/flecs.c
OBJS += Source/main.c

SHDS =
SRCS += Resources/Shaders/BasicRender2D.vert
SRCS += Resources/Shaders/BasicRender2D.frag

zoxel: $(SRCS)
	$(CC) $(CFLAGS) $(SHDS) -o $@ $(OBJS) $(LDLIBS)