# zoxel makefile: [linux, web, android, windows]
#	sudo apt install make && make install-required

# determine the operating system #
ifeq ($(OS),Windows_NT)
    SYSTEM := Windows
else
    SYSTEM := $(shell uname -s)
endif
# compiler tools and flags #
NAME := zoxel
TARGET = build/zoxel
target_dev = build/dev
target_web = build/zoxel.html # .js
target_web2 = zoxel.html # .js
ifeq ($(SYSTEM),Windows)
TARGET = build/zoxel.exe
target_dev = build/dev.exe
endif
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
LDLIBS += -lGL	# opengl linux
LDLIBS += -lvulkan # vulkan on linux
# LDLIBS += -lGLEW
# -lwayland-client
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
ldlibs_web += -lGLEW
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
make_flecs = $(CC) $(flecs_flags) $(CFLAGS) $(fix_flecs_warning) $(CFLAGS_RELEASE) ../$(flecs_source) -o $(flecs_obj) $(LDLIBS2) && echo "  > built [flecs.o]"
make_flecs_lib = ar rcs ../$(flecs_target) $(flecs_obj) && echo "  > built [libflecs.a]"
# build commands
make_release = $(CC) $(CFLAGS) $(fix_flecs_warning) $(CFLAGS_RELEASE) -o ../$(TARGET) $(OBJS) $(LDLIBS) $(LDLIBS2) && echo "  > built [$(TARGET)]"
make_dev = $(CC) $(CFLAGS) $(fix_flecs_warning) $(cflags_debug) -o ../$(target_dev) $(OBJS) $(LDLIBS) $(LDLIBS2)
make_web_release = $(cc_web) $(CFLAGS) $(cflags_web) -o $(target_web2) $(OBJS) ../include/flecs/flecs.c $(ldlibs_web)

# linux & windows #

# release
$(TARGET): $(SRCS)
ifneq ($(SYSTEM),Windows)
	bash bash/util/install_required.sh
endif
	set -e ; \
	bash bash/flecs/check_flecs_lib_not_installed.sh && bash bash/flecs/check_flecs_source.sh && bash bash/flecs/download_flecs_source.sh && cp include/flecs/flecs.h include; \
	bash bash/flecs/check_flecs_lib_not_installed.sh && cd build && $(make_flecs) && $(make_flecs_lib) && cd .. && cp build/libflecs.a lib;  \
	bash bash/flecs/check_flecs_lib.sh && cd build && $(make_release)
	
# bash bash/flecs/check_flecs_lib.sh && cd build && $(make_release)

# development
$(target_dev): $(SRCS)
	bash bash/flecs/check_flecs_lib.sh && cd build && $(make_dev)

# required libraries
install-required:
	bash bash/util/install_required.sh

install-steam-deck-required:
	bash bash/steam/install_on_steam_deck.sh

## installs zoxel into /usr/games directory
install: 
	bash bash/install/install.sh

## uninstalls zoxel into /usr/games directory
uninstall: 
	bash bash/install/uninstall.sh

# run release
run:
	cd build && ./../$(TARGET)

run-headless:
	cd build && ./../$(TARGET) --headless

run-server:
	cd build && ./../$(TARGET) --headless --server

run-tiny:
	cd build && ./../$(TARGET) --tiny

run-medium:
	cd build && ./../$(TARGET) --medium

run-large:
	cd build && ./../$(TARGET) --large

run-vulkan:
	./$(TARGET) --vulkan

# run development
run-dev:
	cd build && ./../$(target_dev)

run-dev-headless:
	cd build && ./../$(target_dev) --headless

run-dev-server:
	cd build && ./../$(target_dev) --headless --server

run-dev-tiny:
	cd build && ./../$(target_dev) --tiny

run-dev-vulkan:
	./$(target_dev) --vulkan

# run development + valgrind
run-dev-debug:
	cd build && valgrind ./../$(target_dev)

run-dev-debug-tiny:
	cd build && valgrind -s ./../$(target_dev) --tiny

run-debug:
ifneq ($(SYSTEM),Windows)
	bash bash/util/install_dev_required.sh
endif
	gdb ./build/dev

#  --leak-check=full

# run release + flecs profiler
run-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(TARGET) --profiler

# run development + flecs profiler
run-dev-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(target_dev) --profiler

run-dev-profiler-tiny:
	sleep 3 && open https://www.flecs.dev/explorer &
	cd build && ./../$(target_dev) --profiler --tiny

# web #

install-web-sdk:
	bash bash/web/install_sdk.sh

# web - bash bash/flecs/check_flecs_lib.sh && 
$(target_web): $(SRCS)
	python3 ~/projects/emsdk/emsdk.py construct_env
	cd build && $(make_web_release)

# Runs zoxel web release build
run-web:
	cd build && ~/projects/emsdk/upstream/emscripten/emrun --browser firefox zoxel.html

# updates the zoxel-play project
update-web:
	bash bash/web/update_zoxel_play.sh

# updates the zoxel-play project
run-zoxel-play:
	bash bash/web/run_zoxel_play.sh

# updates the zoxel-play project
git-push-zoxel-play:
	cd ../zoxel-play && bash/git/git_push.sh

# firefox-esr | firefox
# android #

install-android-sdk:
	bash bash/android/install_required.sh

android:
	bash bash/android/copy_settings.sh
	bash bash/android/install.sh

# bash bash/android/android_copy_sdl.sh

android-run:
	bash bash/android/gradle_run.sh

android-install:
	bash bash/android/gradle_install.sh

android-install-run:
	bash bash/android/gradle_install.sh
	bash bash/android/gradle_run.sh

android-debug:
	bash bash/android/install.sh && bash bash/android/debug_android.sh

android-create-key:
	bash bash/android/generate_keystore.sh

android-dev:
	bash bash/android/install_debug.sh

android-uninstall:
	bash bash/android/gradle_uninstall.sh

android-clean:
	bash bash/android/gradle_clean.sh

debug-android:
	bash bash/android/debug_android.sh

android-update-settings:
	bash bash/android/copy_settings.sh

android-dev-debug:
	bash bash/android/install_debug.sh
	bash bash/android/debug_android.sh

# flecs #

check-flecs:
	open https://github.com/SanderMertens/flecs/releases &

# downloads source into include, installs library into lib
$(flecs_target):
	set -e ; \
	bash bash/flecs/check_flecs_source.sh && bash bash/flecs/download_flecs_source.sh && cp include/flecs/flecs.h include; \
	cd build && $(make_flecs) && $(make_flecs_lib) && cd .. && cp build/libflecs.a lib && cp include/flecs/flecs.h include; \
	echo "  > installed flecs library"

install-sdl:
	bash bash/sdl/install_sdl.sh

install-flecs:
	bash bash/flecs/remove_flecs.sh
	bash bash/flecs/download_flecs_source.sh

remove-flecs:
	bash bash/flecs/remove_flecs.sh

get-nightly-flecs:
	bash bash/flecs/nightly_flecs.sh

get-flecs-version:
	bash bash/flecs/download_flecs_version.sh

revert-nightly-flecs:
	bash bash/flecs/nightly_revert_source.sh

# ssh & git #

git-keys:
	bash bash/ssh/create_ssh.sh

git-push: ## installs zoxel into /usr/games directory
	bash bash/git/git_update_config.sh
	bash bash/git/git_push.sh

git-pull: ## installs zoxel into /usr/games directory
	bash bash/git/git_pull.sh

git-config:
	bash bash/git/git_update_config.sh

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
	bash bash/flecs/remove_flecs.sh

# util #

codeberg:
	open https://codeberg.org/deus/zoxel &

github:
	open https://github.com/deus369/zoxel &

count:
	@echo "Counting Source Files"
	bash bash/count/count_source.sh

list-systems:
	bash bash/zoxel/list_systems.sh

create-system:
	bash bash/zoxel/create_system.sh

zip-build:
	bash bash/util/zip_build.sh

install-play:
	bash bash/install/install_play_button.sh

play:
	gcc tests/glut/play_button.c -o build/play_button -lglut -lGL -lGLU && ./build/play_button &

# lost ones #

help:
	@echo "zoxel -> an open source voxel engine"
	@echo "	latest @ https://codeberg.org/deus/zoxel"
	@echo "  > linux & windows"
	@echo "  make <target>"
	@echo "    play			runs a play button"
	@echo "    install-play		installs a play button"
	@echo "    $(target_dev)			builds development"
	@echo "    <empty>  			builds release"
	@echo "    run				runs $(TARGET)"
	@echo "    run-vulkan			runs $(TARGET) with vulkan"
	@echo "    run-profiler		runs $(TARGET) --profiler"
	@echo "    run-dev			runs $(target_dev)"
	@echo "    run-dev-debug		runs valgrind $(target_dev)"
	@echo "    run-dev-profiler		runs $(target_dev) --profiler"
	@echo "  > web"
	@echo "    install-web-sdk		installs tools for web build"
	@echo "    $(target_web)		builds zoxel-web"
	@echo "    run-web			runs $(target_web)"
	@echo "  > android"
	@echo "    install-android-sdk		installs tools for android build"
	@echo "    android			builds & runs android release"
	@echo "    android-install		installs zoxel apk"
	@echo "    android-run			runs the zoxel apk"
	@echo "    android-dev			builds & runs android debug"
	@echo "    android-dev-debug		builds & runs android debug with logcat"
	@echo "    debug-android		debugs running android game"
	@echo "  > setup"
	@echo "    make $(flecs_target)	builds flecs"
	@echo "    install-required		installs required libraries for debian systems"
	@echo "	   install-steam-deck-required	installs steam required"
	@echo "    install-sdl			installs sdl"
	@echo "    install			installs zoxel"
	@echo "    uninstall			inuninstalls zoxel"
	@echo "    clean			removes all build files"
	@echo "  > util"
	@echo "    count			counts total lines in all source"
	@echo "    list-systems		lists all found zoxel systems in a module"
	@echo "    create-system		creates a new system in a module"
	@echo "    zip-build			zips zoxel build and resources"
	@echo "    github			opens zoxel on github"
	@echo "    codeberg			opens zoxel on codeberg"
	@echo "  > flecs"
	@echo "    check-flecs			checks flecs releases"
	@echo "    install-flecs		installs latest flecs (3.2.6)"
	@echo "    build/libflecs.a		builds flecs library"
	@echo "    remove-flecs		removes flecs library"
	@echo "    get-flecs-version		get a flecs by version"
	@echo "    get-nightly-flecs		gets latest flecs"
	@echo "  > git"
	@echo "    git-pull			pulls latest git"
	@echo "    git-push			pushes git updates (requires ssh access)"
	@echo "    git-keys			creates a ssh key to add to git servers"

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
# cflags_debug += -fsanitize=address # detects memory leaks as well
# cflags_debug += -Wno-stringop-overflow # supresses flecs warning
# cflags_debug += -Wno-stringop-overflow-size
# make something like this so it's less confusing:
# bash bash/flecs/install_flecs.sh
