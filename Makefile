# zoxel makefile built for: linux, webasm, android, windows
#	sudo apt install make
#	remember, put dependent libaries first, followed by core ones
# https://github.com/libsdl-org/SDL/releases/tag/release-2.26.4
# Determine the operating system
ifeq ($(OS),Windows_NT)
    SYSTEM := Windows
else
    SYSTEM := $(shell uname -s)
endif
# Declare compiler tools and flags
NAME := zoxel
TARGET = build/zoxel
TARGET_DEV = build/dev
TARGET_WEB = build/zoxel.js
ifeq ($(SYSTEM),Windows)
TARGET = build/zoxel.exe
TARGET_DEV = build/dev.exe
endif
# used for cleaning
RM = rm
TARGET_WEB_WASM = build/zoxel.wasm
TARGET_WEB_DATA = build/zoxel.data
# our compilers
# Defines the compiler, cc for C code
CC = gcc
# the web compiler
CC_WEB = ~/projects/emsdk/upstream/emscripten/emcc
# OBJS defines all the files used to compile the final Zoxel binary.
OBJS = ../src/main.c
# This collects all c and h files in the directory
# Set the source files
ifeq ($(SYSTEM),Windows)
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
else
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
endif
# our compiler properties
CFLAGS =
# -std=c99 # Specificies c99 Standard
CFLAGS += -std=gnu99
# Needed for a few functions, will be fixed in the future
CFLAGS += -D_DEFAULT_SOURCE
# Position Independent Code https://stackoverflow.com/questions/5311515/gcc-fpic-option
CFLAGS += -fPIC
# supresses flecs warning
CFLAGS += -Wno-stringop-overflow
# CFLAGS += -Wno-stringop-overflow-size
# Add libraries
LDLIBS =
LDLIBS2 =
# for math.h
LDLIBS2 += -lm
# For threading
LDLIBS2 += -lpthread
# For a pre compiled flecs
LDLIBS += -L./ -lflecs
ifeq ($(SYSTEM), Windows)
# opengl windows
LDLIBS += -lopengl32
# win sockets
LDLIBS2 += -lws2_32
else
# opengl linux
LDLIBS += -lGL
endif
# add sdl2 includes
ifeq ($(SYSTEM), Windows)
LDLIBS += -IC:/SDL2/include
LDLIBS += -LC:/SDL2/lib
LDLIBS += -LC:/SDL2_image/lib
LDLIBS += -LC:/SDL2_mixer/lib
endif
# SDL2 Audio Library
LDLIBS += -lSDL2_mixer
# SDL2 Image Library
LDLIBS += -lSDL2_image
# SDL2 Library
LDLIBS += -lSDL2
ifeq ($(SYSTEM), Windows)
LDLIBS += -LSDL2main
LDLIBS += -Wl,-subsystem,windows
LDLIBS += -mwindows
endif
# FOR RELEASE
CFLAGS_RELEASE =
# Optimization Level | -Ofast | -O1 | -O2 | -O3
CFLAGS_RELEASE += -Ofast
# No Debugging
CFLAGS_RELEASE += -D NDEBUG
#  strip - removes 70kb atm
CFLAGS_RELEASE += -s
ifneq ($(SYSTEM),Windows)
# fuse linker plugin on linux
CFLAGS_RELEASE += -flto=auto
endif
# FOR DEBUG
# For Warnings
CFLAGS_DEBUG = -Wall
# Adds debugging info to executeable
CFLAGS_DEBUG += -g
# CFLAGS_DEBUG += -fsanitize=address # detects memory leaks as well
# CFLAGS_DEBUG += -Wno-stringop-overflow # supresses flecs warning
# CFLAGS_DEBUG += -Wno-stringop-overflow-size
# web build flags
CFLAGS_WEB = --preload-file resources
CFLAGS_WEB += -s WASM=1
CFLAGS_WEB += -s FULL_ES3=1
CFLAGS_WEB += -s USE_WEBGL2=1
CFLAGS_WEB += -s MIN_WEBGL_VERSION=2
CFLAGS_WEB += -s MAX_WEBGL_VERSION=2
CFLAGS_WEB += -s ALLOW_MEMORY_GROWTH
CFLAGS_WEB += -s STACK_SIZE=365536
# libraries used in web build
LDLIBS_WEB = -lGL
LDLIBS_WEB += -lSDL
LDLIBS_WEB += -s USE_SDL=2
LDLIBS_WEB += -s USE_SDL_IMAGE=2
LDLIBS_WEB += -s SDL2_IMAGE_FORMATS='["png"]' # "bmp",
LDLIBS_WEB += -s USE_SDL_MIXER=2
LDLIBS_WEB += -L./ -lflecs
# flecs
flecs_target = build/libflecs.a
flecs_source = include/flecs/flecs.c
flecs_flags = -c
flecs_obj = flecs.o
# Completed build commands
MAKE_RELEASE = $(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o ../$(TARGET) $(OBJS) $(LDLIBS) $(LDLIBS2)
MAKE_DEV = $(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o ../$(TARGET_DEV) $(OBJS) $(LDLIBS) $(LDLIBS2)
MAKE_WEB_RELEASE = $(CC_WEB) $(CFLAGS) $(CFLAGS_WEB) -o ../$(TARGET_WEB) $(OBJS) $(LDLIBS_WEB)
make_flecs = $(CC) $(flecs_flags) $(CFLAGS) $(CFLAGS_RELEASE) ../$(flecs_source) -o $(flecs_obj) $(LDLIBS2)
make_flecs_lib = ar rcs ../$(flecs_target) $(flecs_obj)

# release
$(TARGET): $(SRCS)
	bash bash/flecs/check_flecs_lib.sh && cd build && $(MAKE_RELEASE)

# dev
$(TARGET_DEV): $(SRCS)
	bash bash/flecs/check_flecs_lib.sh && cd build && $(MAKE_DEV)

# web
$(TARGET_WEB): $(SRCS)
	python3 ~/projects/emsdk/emsdk.py construct_env
	bash bash/flecs/check_flecs_lib.sh && cd build && $(MAKE_WEB_RELEASE)

# flecs $(flecs_source)
$(flecs_target):
	set -e ; \
	bash bash/flecs/check_flecs.sh && cd bash/flecs && bash install_flecs.sh ; \
	cd build && $(make_flecs) && $(make_flecs_lib)

# builds for all platforms - this rebuilds everytime tho
all: $(SRCS)
	@echo "Begin Making All"
	@echo "Installing/Making Flecs [$(flecs_target)]"
	cd bash/flecs && bash install_flecs.sh
	cd build && $(make_flecs) && $(make_flecs_lib)
	@echo "Making Native Release Build [$(TARGET)]"
	cd build && $(MAKE_RELEASE)
	@echo "Making Native Dev Build [$(TARGET_DEV)]"
	cd build && $(MAKE_DEV)
	@echo "Finished Making All"

# @echo "Making Webasm Release Build [$(TARGET_WEB)]"
# cd build && $(MAKE_WEB_RELEASE)

# Removes all build files
clean:
	@echo "Cleaning All Build Files"
	cd bash/flecs && bash remove_flecs.sh

count:
	@echo "Counting Source Files"
	bash bash/count/count_source.sh

# todo ignore resources directory and gitignore file here
# $(RM) build/*.o

# Runs zoxel release build
run:
	cd build && ./../$(TARGET)

# Runs zoxel dev build
run-dev:
	cd build && ./../$(TARGET_DEV)

# Runs zoxel dev build with valgrind
run-dev-debug:
	cd build && valgrind ./../$(TARGET_DEV)

run-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(TARGET) --profiler

run-dev-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(TARGET_DEV) --profiler

# Runs zoxel web release build
run-web:
	cd build && emrun --browser firefox index.html

android:
	bash/android/install.sh

android-dev:
	bash/android/install_debug.sh

android-dev-debug:
	bash/android/install_debug.sh
	bash/android/read_logcat.sh

install: ## installs zoxel into /usr/games directory
	cd bash/install && bash install.sh

uninstall: ## uninstalls zoxel into /usr/games directory
	bash/install/uninstall.sh
	
install-required:
	@echo "Installing Libaries: make gcc"
	sudo apt install gcc
	bash bash/sdl/install_sdl.sh

install-web-sdk:
	bash bash/web/install_sdk.sh

install-sdl:
	bash bash/sdl/install_sdl.sh

install-flecs:
	cd bash/flecs && bash install_flecs.sh

create-ssh:
	bash bash/ssh/create_ssh.sh

remove-flecs:
	cd bash/flecs && bash remove_flecs.sh

git-push: ## installs zoxel into /usr/games directory
	cd bash/git && bash git_push.sh

git-pull: ## installs zoxel into /usr/games directory
	cd bash/git && bash git_pull.sh

help:
	@echo "zoxel -> an open source voxel engine"
	@echo "  make $(flecs_target)	builds flecs"
	@echo "  make			builds zoxel"
	@echo "  make <target>"
	@echo "    $(TARGET_DEV)			builds dev"
	@echo "    $(TARGET_WEB)		builds zoxel-web"
	@echo "    run			runs $(TARGET)"
	@echo "    run-profiler	runs $(TARGET) --profiler"
	@echo "    run-dev		runs $(TARGET_DEV)"
	@echo "    run-dev-debug	runs valgrind $(TARGET_DEV)"
	@echo "    run-dev-profiler	runs $(TARGET_DEV) --profiler"
	@echo "    run-web		runs $(TARGET_WEB)"
	@echo "    clean		removes all build files"
	@echo "    count		counts total lines in all source"
	@echo "    install		installs zoxel"
	@echo "    uninstall		inuninstalls zoxel"
	@echo "    install-sdl		installs sdl"
	@echo "    install-web-sdk	installs emcc for web build"
	@echo "    android		builds & runs android release"
	@echo "    android-dev		builds & runs android debug"
	@echo "    android-dev-debug	builds & runs android debug with logcat"
	@echo "    install-required	installs required libraries for debian systems"
	@echo "    create-ssh		creates a ssh key to add to git servers"
	@echo "    git-pull		pulls latest git"
	@echo "    git-push		pushes git updates - if has ssh access"
	@echo "find latest at -> https://codeberg.org/deus/zoxel"

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

# can add --num-callers=60 to valgrind
# \todo atm: put all platform builds into this one file
#	make web, or make android, or make windows, or make dev, make is for make linux

# used to remove web?
# $(RM) $(TARGET_WEB)
# $(RM) $(TARGET_WEB_WASM)
# $(RM) $(TARGET_WEB_DATA)

# $(RM) $(TARGET)
# $(RM) $(TARGET_DEV)
# $(RM) $(flecs_target)

# LDLIBS += -s SDL2_IMAGE_FORMATS='["png"]' # "bmp",
# used for manual sdl compiling on systems that don't have sdl lib in their package managers
# LDLIBS += -L/usr/local/lib
# LDLIBS += -Wl,-rpath=/usr/local/lib