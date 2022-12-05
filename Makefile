# Zoxel Makefile!
# can add --num-callers=60 to valgrind

# Declare compiler tools and flags
TARGET = builds/zoxel
CC = cc						# Defines the compiler, cc for C code
CFLAGS = -std=c99			# Specificies c99 Standard
# CFLAGS += -fPIC				# Position Independent Code https://stackoverflow.com/questions/5311515/gcc-fpic-option
CFLAGS += -D_DEFAULT_SOURCE	# Needed for a few functions, will be fixed in the future
# CFLAGS += -Wall				# For Warnings
# FOR RELEASE
CFLAGS += -O3				# Optimization level 3
CFLAGS += -flto=auto		# fuse linker plugin
CFLAGS += -D NDEBUG		# No Debugging
# Add libraries
LDLIBS = -lGL				# OpenGL library
LDLIBS += -lSDL2			# SDL2 Library
LDLIBS += -lSDL2_image		# SDL2 Image Library
LDLIBS += -lSDL2_mixer		# SDL2 Audio Library
# LDLIBS += -SDL2_IMAGE_FORMATS='["png"]'
LDLIBS += -lm				# for math.h
# OBJS defines all the files used to compile the final Zoxel binary.
OBJS = include/flecs.c src/main.c
# This collects all c and h files in the directory
SRCS = $(shell find src/ -type f -name *.c)
SRCS += $(shell find src/ -type f -name *.h)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

clear:
	$(RM) $(TARGET)

# CFLAGS += -D_POSIX_C_SOURCE=200112L
# dCFLAGS += -fsanitize=undefined
# LDLIBS += -flto-partition=none ?
# https://stackoverflow.com/questions/66350310/link-time-optimizations-in-cuda-11-what-are-they-and-how-to-use-them
# LDLIBS += -dlto	# Dynamic Link-Time Optimization