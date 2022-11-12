# Zoxel Makefile!

# can add --num-callers=60 to valgrind

# Declare compiler tools and flags
TARGET = zoxel
CC = cc						# Defines the compiler, cc for C code
CFLAGS = -std=c99			# Specificies c99 Standard
# CFLAGS += -fPIC			# Position Independent Code https://stackoverflow.com/questions/5311515/gcc-fpic-option
CFLAGS += -D_DEFAULT_SOURCE	# Needed for a few functions, will be fixed in the future
CFLAGS += -Wall				# For Warnings
# DEV MODE
# CFLAGS += -g				# Adds debugging info to executeable
# CFLAGS += -fsanitize=address	# detects memory leaks as well
# FOR RELEASE
CFLAGS += -O3				# Optimization level 3
CFLAGS += -flto=auto		# fuse linker plugin
CFLAGS += -D NDEBUG		# No Debugging
# Add libraries
LDLIBS = -lGL				# OpenGL library
LDLIBS += -lSDL2			# SDL2 Library
LDLIBS += -lSDL2_image		# SDL2 Image Library
# LDLIBS += -SDL2_IMAGE_FORMATS='["png"]'
LDLIBS += -lm				# for math.h

# dCFLAGS += -fsanitize=undefined

# LDLIBS += -flto-partition=none ?
# https://stackoverflow.com/questions/66350310/link-time-optimizations-in-cuda-11-what-are-they-and-how-to-use-them
# LDLIBS += -dlto	# Dynamic Link-Time Optimization

# SRCS defines all the files that will be used in the game.
SRCS = 
SRCS += imports/flecs.c 
SRCS += imports/flecs.h
SRCS += src/main.c
# imports
SRCS += src/core/apps/util/sdl_util.c
SRCS += src/core/apps/util/flecs_util.c
# gameplay
# players
SRCS += src/space/players/players.c
# rendering
SRCS += src/core/rendering/rendering.c
SRCS += src/core/rendering/core/rendering_core.c

# OBJS defines all the files used to compile Zoxel.
OBJS = 
OBJS += imports/flecs.c
OBJS += src/main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

clear:
	$(RM) $(TARGET)

# CFLAGS += -D_POSIX_C_SOURCE=200112L