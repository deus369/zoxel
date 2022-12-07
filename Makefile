# Zoxel Makefile!
# can add --num-callers=60 to valgrind
# \todo atm: put all platform builds into this one file
#	make web, or make android, or make windows, or make dev, make is for make linux

# Declare compiler tools and flags
NAME := Zoxel
TARGET = zoxel
TARGET_DEV = zoxel-dev
TARGET_WEB = web/zoxel.js
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
# LDLIBS += -s SDL2_IMAGE_FORMATS='["png"]' # "bmp",
LDLIBS += -lSDL2_mixer		# SDL2 Audio Library
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
CC_WEB = emcc
CFLAGS_WEB = --preload-file resources
CFLAGS_WEB += -s WASM=1
CFLAGS_WEB += -s FULL_ES3=1
CFLAGS_WEB += -s USE_WEBGL2=1
CFLAGS_WEB += -s MIN_WEBGL_VERSION=2
CFLAGS_WEB += -s MAX_WEBGL_VERSION=2
CFLAGS_WEB += -s ALLOW_MEMORY_GROWTH
CFLAGS_WEB += -s STACK_SIZE=365536
LDLIBS_WEB = -lGL
LDLIBS_WEB += -lSDL
LDLIBS_WEB += -s USE_SDL=2
LDLIBS_WEB += -s USE_SDL_IMAGE=2
LDLIBS_WEB += -s SDL2_IMAGE_FORMATS='["png"]' # "bmp",
LDLIBS_WEB += -s USE_SDL_MIXER=2

all: $(TARGET) ## builds zoxel

# release
$(TARGET): $(SRCS) ## builds zoxel
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $@ $(OBJS) $(LDLIBS)

# dev
$(TARGET_DEV): $(SRCS) ## builds zoxel
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o $@ $(OBJS) $(LDLIBS)

# web
$(TARGET_WEB): $(SRCS) ## builds zoxel
	$(CC_WEB) $(CFLAGS) $(CFLAGS_WEB) -o $@ $(OBJS) $(LDLIBS_WEB)

clean: ## removes zoxel build
	$(RM) $(TARGET)

run: # $(TARGET) ## builds zoxel
	./$(TARGET)

run-dev: # runs zoxel-dev
	./$(TARGET_DEV)

run-dev-debug: # runs valgrind zoxel-dev
	valgrind ./$(TARGET_DEV)

run-web:
	emrun --browser firefox web/index.html

install: ## installs zoxel into /usr/games directory
	bash/install/install.sh

uninstall: ## uninstalls zoxel into /usr/games directory
	bash/install/uninstall.sh

install-web-builder:
	bash/web/install_emcc.sh

help:
	@echo "zoxel -> an open source voxel engine"
	@echo "  make <target>:"
	@echo "    run			runs $(TARGET)"
	@echo "    $(TARGET_DEV)	builds zoxel-dev"
	@echo "    $(TARGET_WEB)	builds zoxel-web"
	@echo "    run-dev		runs $(TARGET_DEV)"
	@echo "    run-dev-debug	runs valgrind $(TARGET_DEV)"
	@echo "    run-web		runs $(TARGET_WEB)"
	@echo "    install		installs zoxel"
	@echo "    uninstall		inuninstalls zoxel"
	@echo "    install-web-builder	installs emcc for web build"
	@echo "    clean		removes zoxel build"
	@echo "    just make		builds zoxel"
	@echo "latest -> https://codeberg.org/deus/zoxel"

# CFLAGS += -D_POSIX_C_SOURCE=200112L
# dCFLAGS += -fsanitize=undefined
# LDLIBS += -flto-partition=none ?
# https://stackoverflow.com/questions/66350310/link-time-optimizations-in-cuda-11-what-are-they-and-how-to-use-them
# LDLIBS += -dlto	# Dynamic Link-Time Optimization
# @echo " Inside Directory: $(CURDIR)"
# . $(CURDIR)/bash/web/emsdk_env.sh
# web build threading
# LDLIBS += -s USE_PTHREADS=1
# LDLIBS += -s PTHREAD_POOL_SIZE=2