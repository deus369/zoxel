# Zoxel Makefile!
# can add --num-callers=60 to valgrind
# \todo atm: put all platform builds into this one file
#	make web, or make android, or make windows, or make dev, make is for make linux

# Declare compiler tools and flags
NAME := Zoxel
TARGET = builds/zoxel
TARGET_DEV = builds/zoxel-dev
# OBJS defines all the files used to compile the final Zoxel binary.
OBJS = include/flecs.c src/main.c
# This collects all c and h files in the directory
SRCS = $(shell find src/ -type f -name *.c)
SRCS += $(shell find src/ -type f -name *.h)
# our compiler properties
CC = cc						# Defines the compiler, cc for C code
CFLAGS = -std=c99			# Specificies c99 Standard
CFLAGS += -D_DEFAULT_SOURCE	# Needed for a few functions, will be fixed in the future
CFLAGS += -fPIC				# Position Independent Code https://stackoverflow.com/questions/5311515/gcc-fpic-option
# Add libraries
LDLIBS = -lGL				# OpenGL library
LDLIBS += -lSDL2			# SDL2 Library
LDLIBS += -lSDL2_image		# SDL2 Image Library
LDLIBS += -lSDL2_mixer		# SDL2 Audio Library
# LDLIBS += -SDL2_IMAGE_FORMATS='["png"]'
LDLIBS += -lm				# for math.h
# used for manual sdl compiling on systems that don't have sdl lib in their package managers
LDLIBS += -L/usr/local/lib
LDLIBS += -Wl,-rpath=/usr/local/lib
# FOR RELEASE
CFLAGS_RELEASE = -O3				# Optimization level 3
CFLAGS_RELEASE += -flto=auto		# fuse linker plugin
CFLAGS_RELEASE += -D NDEBUG			# No Debugging
# FOR DEBUG
CFLAGS_DEBUG = -Wall				# For Warnings
CFLAGS_DEBUG += -g					# Adds debugging info to executeable
# CFLAGS_DEBUG += -fsanitize=address # detects memory leaks as well

all: $(TARGET) ## builds zoxel

# release
$(TARGET): $(SRCS) ## builds zoxel
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $(TARGET) $(OBJS) $(LDLIBS)

# dev
$(TARGET_DEV): $(SRCS) ## builds zoxel
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o $(TARGET_DEV) $(OBJS) $(LDLIBS)

# .PHONY: build $(TARGET)
build: $(SRCS) ## builds zoxel
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $(TARGET) $(OBJS) $(LDLIBS)

clean: ## removes zoxel build
	$(RM) $(TARGET)

run: # $(TARGET) ## builds zoxel
	./$(TARGET)

run-dev: # runs zoxel-dev
	./$(TARGET_DEV)

run-dev-debug: # runs valgrind zoxel-dev
	valgrind ./$(TARGET_DEV)

install: ## installs zoxel into /usr/games directory
	bash/install/install.sh

uninstall: ## uninstalls zoxel into /usr/games directory
	bash/install/uninstall.sh

help:
	@echo "Welcome to $(NAME)!"
	@echo "---------- ---------- ---------- ---------- ---------- ----------"
	@echo "Use 'make <target>':"
	@echo "  just make		builds zoxel into builds directory"
	@echo "  run			runs $(TARGET)"
	@echo "  $(TARGET_DEV)	builds zoxel-dev"
	@echo "  run-dev		runs $(TARGET_DEV)"
	@echo "  run-dev-debug	runs valgrind $(TARGET_DEV)"
	@echo "  install		installs zoxel into /usr/games directory"
	@echo "  uninstall		removes zoxel from /usr/games directory"
	@echo "  clean			removes zoxel from build directory"
	@echo "---------- ---------- ---------- ---------- ---------- ----------"
	@echo "--- zoxel at https://codeberg.org/deus/zoxel ---"
	@echo ""

# CFLAGS += -D_POSIX_C_SOURCE=200112L
# dCFLAGS += -fsanitize=undefined
# LDLIBS += -flto-partition=none ?
# https://stackoverflow.com/questions/66350310/link-time-optimizations-in-cuda-11-what-are-they-and-how-to-use-them
# LDLIBS += -dlto	# Dynamic Link-Time Optimization