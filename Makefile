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
target_dev = build/dev
target_web = build/zoxel.html # .js
target_web2 = zoxel.html # .js
ifeq ($(SYSTEM),Windows)
TARGET = build/zoxel.exe
target_dev = build/dev.exe
endif
# used for cleaning
RM = rm
web_wasm_file = build/zoxel.wasm
web_data_file = build/zoxel.data
# our compilers
# Defines the compiler, cc for C code
CC = gcc
# the web compiler
cc_web = ~/projects/emsdk/upstream/emscripten/emcc
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
# c99 | gnu99
CFLAGS += -std=gnu99
# Needed for a few functions, will be fixed in the future
CFLAGS += -D_DEFAULT_SOURCE
# Position Independent Code https://stackoverflow.com/questions/5311515/gcc-fpic-option
CFLAGS += -fPIC
# supresses flecs warning
fix_flecs_warning = -Wno-stringop-overread -Wno-stringop-overflow
# CFLAGS += -Wno-stringop-overflow-size
# Add libraries
LDLIBS =
LDLIBS2 =
# for math.h
LDLIBS2 += -lm
# For threading
LDLIBS2 += -lpthread
# For a pre compiled flecs
LDLIBS += -L../lib -lflecs
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
cflags_debug = -Wall
# Adds debugging info to executeable
cflags_debug += -g
# cflags_debug += -fsanitize=address # detects memory leaks as well
# cflags_debug += -Wno-stringop-overflow # supresses flecs warning
# cflags_debug += -Wno-stringop-overflow-size
# web build flags
cflags_web = --preload-file resources
cflags_web += -s WASM=1
cflags_web += -s FULL_ES3=1
cflags_web += -s USE_WEBGL2=1
cflags_web += -s MIN_WEBGL_VERSION=2
cflags_web += -s MAX_WEBGL_VERSION=2
cflags_web += -s ALLOW_MEMORY_GROWTH
cflags_web += -s STACK_SIZE=365536
cflags_web += -s EXPORTED_FUNCTIONS=['_main','_ntohs']
# libraries used in web build
ldlibs_web = -lGL
ldlibs_web += -lSDL
ldlibs_web += -s USE_SDL=2
ldlibs_web += -s USE_SDL_IMAGE=2
ldlibs_web += -s SDL2_IMAGE_FORMATS='["png"]' # "bmp",
ldlibs_web += -s USE_SDL_MIXER=2
# ldlibs_web += -L./ -lflecs
# flecs
flecs_target = build/libflecs.a
flecs_source = include/flecs/flecs.c
flecs_flags = -c
flecs_obj = flecs.o
make_flecs = $(CC) $(flecs_flags) $(CFLAGS) $(fix_flecs_warning) $(CFLAGS_RELEASE) ../$(flecs_source) -o $(flecs_obj) $(LDLIBS2)
make_flecs_lib = ar rcs ../$(flecs_target) $(flecs_obj)
# build commands
make_release = $(CC) $(CFLAGS) $(fix_flecs_warning) $(CFLAGS_RELEASE) -o ../$(TARGET) $(OBJS) $(LDLIBS) $(LDLIBS2)
make_dev = $(CC) $(CFLAGS) $(fix_flecs_warning) $(cflags_debug) -o ../$(target_dev) $(OBJS) $(LDLIBS) $(LDLIBS2)
make_web_release = $(cc_web) $(CFLAGS) $(cflags_web) -o $(target_web2) $(OBJS) ../include/flecs/flecs.c $(ldlibs_web)

# linux & windows #

# release
$(TARGET): $(SRCS)
	bash bash/flecs/check_flecs_lib.sh && cd build && $(make_release)

# development
$(target_dev): $(SRCS)
	bash bash/flecs/check_flecs_lib.sh && cd build && $(make_dev)

# required libraries
install-required:
	@echo "Installing Libaries: make gcc"
	sudo apt install gcc
	bash bash/sdl/install_sdl.sh

## installs zoxel into /usr/games directory
install: 
	cd bash/install && bash install.sh

## uninstalls zoxel into /usr/games directory
uninstall: 
	bash/install/uninstall.sh

# run release
run:
	cd build && ./../$(TARGET)

# run development
run-dev:
	cd build && ./../$(target_dev)

# run development + valgrind
run-dev-debug:
	cd build && valgrind ./../$(target_dev)

# run release + flecs profiler
run-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(TARGET) --profiler

# run development + flecs profiler
run-dev-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(target_dev) --profiler

# web #

install-web-sdk:
	bash bash/web/install_sdk.sh

# web - bash bash/flecs/check_flecs_lib.sh && 
$(target_web): $(SRCS)
	python3 ~/projects/emsdk/emsdk.py construct_env
	cd build && $(make_web_release)

# Runs zoxel web release build
run-web:
	cd build && ~/projects/emsdk/upstream/emscripten/emrun --browser firefox-esr zoxel.html

# android #

install-android-sdk:
	bash bash/android/install_required.sh

android:
	bash bash/android/install.sh

android-create-key:
	bash bash/android/generate_keystore.sh

android-dev:
	bash bash/android/install_debug.sh

android-uninstall:
	bash bash/android/gradle_uninstall.sh

android-clean:
	bash bash/android/gradle_clean.sh

android-debug:
	bash bash/android/debug_android.sh

android-update-settings:
	bash bash/android/copy_settings.sh

android-dev-debug:
	bash bash/android/install_debug.sh
	bash bash/android/debug_android.sh

# flecs #

# $(flecs_source)
# downloads source into include, installs library into lib
$(flecs_target):
	set -e ; \
	bash bash/flecs/check_flecs_source.sh && bash bash/flecs/download_flecs_source.sh && cp include/flecs/flecs.h include; \
	cd build && $(make_flecs) && $(make_flecs_lib) && cd .. && cp build/libflecs.a lib && echo "  > installed flecs library"

install-sdl:
	bash bash/sdl/install_sdl.sh

install-flecs:
	bash bash/flecs/download_flecs_source.sh

remove-flecs:
	bash remove_flecs.sh

get-nightly-flecs:
	bash bash/flecs/nightly_flecs.sh

revert-nightly-flecs:
	bash bash/flecs/nightly_revert_source.sh

# ssh & git #

create-ssh:
	bash bash/ssh/create_ssh.sh

git-push: ## installs zoxel into /usr/games directory
	cd bash/git && bash git_push.sh

git-pull: ## installs zoxel into /usr/games directory
	cd bash/git && bash git_pull.sh

# all platforms #

# builds for all platforms - this rebuilds everytime tho
all: $(SRCS)
	@echo "Begin Making All"
	@echo "Installing/Making Flecs [$(flecs_target)]"
	bash bash/flecs/download_flecs_source.sh
	cd build && $(make_flecs) && $(make_flecs_lib)
	@echo "Making Native Release Build [$(TARGET)]"
	cd build && $(make_release)
	@echo "Making Native Dev Build [$(target_dev)]"
	cd build && $(make_dev)
	@echo "Finished Making All"

# removes all build files
clean:
	@echo "Cleaning All Build Files"
	bash remove_flecs.sh

# util #

count:
	@echo "Counting Source Files"
	bash bash/count/count_source.sh

# lost ones #

help:
	@echo "zoxel -> an open source voxel engine"
	@echo "  make $(flecs_target)	builds flecs"
	@echo "  make			builds zoxel"
	@echo "  make <target>"
	@echo "    $(target_dev)			builds dev"
	@echo "    $(target_web)		builds zoxel-web"
	@echo "    run			runs $(TARGET)"
	@echo "    run-profiler	runs $(TARGET) --profiler"
	@echo "    run-dev		runs $(target_dev)"
	@echo "    run-dev-debug	runs valgrind $(target_dev)"
	@echo "    run-dev-profiler	runs $(target_dev) --profiler"
	@echo "    run-web		runs $(target_web)"
	@echo "    clean		removes all build files"
	@echo "    count		counts total lines in all source"
	@echo "    install		installs zoxel"
	@echo "    uninstall		inuninstalls zoxel"
	@echo "    install-sdl		installs sdl"
	@echo "    install-web-sdk	installs tools for web build"
	@echo "    install-android-sdk	installs tools for android build"
	@echo "    android		builds & runs android release"
	@echo "    android-dev		builds & runs android debug"
	@echo "    android-dev-debug	builds & runs android debug with logcat"
	@echo "    install-required	installs required libraries for debian systems"
	@echo "    create-ssh		creates a ssh key to add to git servers"
	@echo "    git-pull		pulls latest git"
	@echo "    git-push		pushes git updates - if has ssh access"
	@echo "find latest at -> https://codeberg.org/deus/zoxel"

# todo: clean more
# ignore resources directory and gitignore in build?
# $(RM) build/*.o
# used to remove web?
# $(RM) $(target_web)
# $(RM) $(web_wasm_file)
# $(RM) $(web_data_file)
# $(RM) $(TARGET)
# $(RM) $(target_dev)
# $(RM) $(flecs_target)

# use these?
# LDLIBS += -s SDL2_IMAGE_FORMATS='["png"]' # "bmp",
# CFLAGS += -D_POSIX_C_SOURCE=200112L
# dCFLAGS += -fsanitize=undefined
# LDLIBS += -flto-partition=none ?
# https://stackoverflow.com/questions/66350310/link-time-optimizations-in-cuda-11-what-are-they-and-how-to-use-them
# LDLIBS += -dlto	# Dynamic Link-Time Optimization
# web build threading
# LDLIBS += -s USE_PTHREADS=1
# LDLIBS += -s PTHREAD_POOL_SIZE=2
# can add --num-callers=60 to valgrind
# used for manual sdl compiling on systems that don't have sdl lib in their package managers
# LDLIBS += -L/usr/local/lib
# LDLIBS += -Wl,-rpath=/usr/local/lib