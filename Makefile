# ===== ===== ===== #
# ===== ===== ===== #
# ===== zoxel ===== #
# ===== ===== ===== #
# ===== ===== ===== #

# platforms [linux, windows, web, android]
# stores [steam, itch, google]
# tooling: sudo apt install make && make install-required

resources_dir = build/resources
LDLIBS = -Llib -lflecs -lSDL2_mixer -lSDL2_image -lSDL2 -lm -lpthread
# determine the operating system #
ifeq ($(OS),Windows_NT)
    SYSTEM := Windows
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
    LDLIBS += -lopengl32 -lws2_32
    LDLIBS += -IC:/SDL2/include -LC:/SDL2/lib -LC:/SDL2_image/lib -LC:/SDL2_mixer/lib # add sdl2 includes
    LDLIBS += -LSDL2main -Wl,-subsystem,windows -mwindows # add libraries
else # linux
    SYSTEM := $(shell uname -s)
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
    LDLIBS += -lGL
endif
# collect our source files #
CFLAGS = -std=gnu99 -D_DEFAULT_SOURCE -fPIC
# supresses flecs warning
CFLAGS += -Wno-stringop-overread -Wno-stringop-overflow

# ===== ===== ===== #
# ===== linux ===== #
# ===== ===== ===== #

target = build/linux/zoxel
CC = gcc # c99 | gnu99
OBJS = src/main.c
ifeq ($(SYSTEM),Windows)
target = build/zoxel.exe
endif
CFLAGS_RELEASE = -Ofast -D NDEBUG -s
ifneq ($(SYSTEM),Windows)
CFLAGS_RELEASE += -flto=auto # fuse linker plugin on linux only
endif
make_release = $(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $(target) $(OBJS) $(LDLIBS)

$(target): $(SRCS)
	$(make_release)

linux:
	$(make_release)

# required libraries
install-required:
	bash bash/util/install_required.sh

## installs zoxel into /usr/games directory
install: 
	bash bash/install/install.sh

## uninstalls zoxel into /usr/games directory
uninstall: 
	bash bash/install/uninstall.sh

# run release
run:
	./$(target)

run-headless:
	./$(target) --headless

run-server:
	./$(target) --headless --server

run-tiny:
	./$(target) --tiny

run-medium:
	./$(target) --medium

run-large:
	./$(target) --large

run-vulkan:
	./$(target) --vulkan


# ====== ======= ====== #
# ===== linux-dev ===== #
# ====== ======= ====== #

target_dev = build/linux-dev/zoxel
ifeq ($(SYSTEM),Windows)
target_dev = build/windows-dev/zoxel.exe
endif
cflags_debug = -Wall -g
make_dev = $(CC) $(CFLAGS) $(cflags_debug) -o $(target_dev) $(OBJS) $(LDLIBS)

# development
dev:
	$(make_dev)

$(target_dev): $(SRCS)
	$(make_dev)

run-dev:
	./$(target_dev)

run-dev-headless:
	./$(target_dev) --headless

run-dev-server:
	./$(target_dev) --headless --server

run-dev-tiny:
	./$(target_dev) --tiny

run-dev-vulkan:
	./$(target_dev) --vulkan

# run development + valgrind
run-dev-debug:
	valgrind ./$(target_dev)

run-dev-debug-tiny:
	valgrind -s ./$(target_dev) --tiny

run-debug:
	gdb ./$(target_dev)

# run release + flecs profiler
run-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	./$(target) --profiler

# run development + flecs profiler
run-dev-profiler:
	sleep 3 && open https://www.flecs.dev/explorer &
	./$(target_dev) --profiler

run-dev-profiler-tiny:
	sleep 3 && open https://www.flecs.dev/explorer &
	./$(target_dev) --profiler --tiny


# ===== ===== ===== #
# ===== flecs ===== #
# ===== ===== ===== #

flecs_target = build/libflecs.a
flecs_source = include/flecs/flecs.c
flecs_flags = -c
flecs_obj = build/flecs.o
flecs_libs = -lm -lpthread
ifeq ($(SYSTEM), Windows) # win sockets
flecs_libs += -lws2_32
endif
make_flecs = $(CC) $(flecs_flags) $(CFLAGS) $(CFLAGS_RELEASE) $(flecs_source) -o $(flecs_obj) $(flecs_libs)
make_flecs_lib = ar rcs $(flecs_target) $(flecs_obj)
make_flecs_big= set -e; \
	bash bash/flecs/check_flecs_source.sh && bash bash/flecs/download_flecs_source.sh && \
	cp include/flecs/flecs.h include; \
	$(make_flecs) && \
	$(make_flecs_lib)  && \
	cp build/libflecs.a lib && \
	cp include/flecs/flecs.h include

# downloads source into include, installs library into lib
$(flecs_target):
	$(make_flecs_big)

flecs:
	$(make_flecs_big)

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

check-flecs:
	open https://github.com/SanderMertens/flecs/releases &

# ====== ===== ====== #
# ===== windows ===== #
# ====== ===== ====== #
# [from linux]

cc_windows=x86_64-w64-mingw32-gcc
target_windows = build/windows/zoxel.exe
windows_includes = -Iinclude -I/usr/include/SDL2 -I/usr/include/GL
windows_pre_libs = -Llib -Lbin -Lbuild/sdl/sdl/build/.libs -Lbuild/sdl/sdl_mixer/build/.libs -Lbuild/sdl/sdl_image/.libs
windows_libs = -lSDL2_mixer -lSDL2_image -lSDL2 -lm -lpthread -lws2_32 -mwindows -Wl,-subsystem,windows -lglew32 -lopengl32
make_windows = $(cc_windows) $(OBJS) include/flecs/flecs.c -o $(target_windows) $(windows_pre_libs) $(windows_includes) $(windows_libs)

windows-sdk:
	bash bash/windows/install_sdk.sh

run-windows:
	WINEPATH=bin wine build/windows/zoxel.exe

run-windows-debug:
	WINEDEBUG=+opengl wine build/windows/zoxel.exe

# todo: copy resources and bin dll's into the folder build/windows
ifneq ($(SYSTEM),Windows)
$(target_windows): $(SRCS)
	@echo " > building windows in linux"
	$(make_windows)

windows:
	@echo " > building windows in linux"
	$(make_windows)
endif

# ======= ===== ======= #
# ===== windows32 ===== #
# ======= ===== ======= #

cc_windows_32=i686-w64-mingw32-gcc
target_windows_32 = build/windows_32/zoxel_32.exe

# todo: windows 32 build, linux32, etc


# ==== ===== ==== #
# ===== web ===== #
# ==== ===== ==== #

cc_web = ~/projects/emsdk/upstream/emscripten/emcc
emrun=~/projects/emsdk/upstream/emscripten/emrun
emsdk=python3 ~/projects/emsdk/emsdk.py
target_web_dir = build/web
target_web = $(target_web_dir)/zoxel.html # .js
web_wasm_file = $(target_web_dir)/zoxel.wasm
web_data_file = $(target_web_dir)/zoxel.data
make_web_checks= [ ! -d $(target_web_dir) ] && mkdir -p $(target_web_dir); \
[ ! -d $(target_web_dir)/resources ] && cp -R $(resources_dir) $(target_web_dir)/resources;
web_resources_dir = -Dresources_dir_name="\"build/resources\""
cflags_web = --preload-file $(resources_dir) -s WASM=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s ALLOW_MEMORY_GROWTH -s STACK_SIZE=365536 -s EXPORTED_FUNCTIONS=['_main','_ntohs']
ldlibs_web = -lGL -lGLEW -lSDL -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_MIXER=2
make_web = $(make_web_checks) $(emsdk) construct_env && $(cc_web) $(CFLAGS) $(cflags_web) $(web_resources_dir) -o $(target_web) $(OBJS) include/flecs/flecs.c $(ldlibs_web)

$(target_web): $(SRCS)
	$(make_web)

web:
	$(make_web)

# Runs zoxel web release build
run-web:
	$(emrun) $(target_web)

# ~/projects/emsdk/upstream/emscripten/emrun --browser firefox zoxel.html

# todo: download zoxel-play for web live on git

# updates the zoxel-play project
update-web:
	bash bash/web/update_zoxel_play.sh

# updates the zoxel-play project
run-zoxel-play:
	bash bash/web/run_zoxel_play.sh

# updates the zoxel-play project
git-push-zoxel-play:
	echo " > pushing from projects/zoxel-play"
	cd ../zoxel-play && bash/git/git_push.sh

web-sdk:
	bash bash/web/install_sdk.sh

# ====== ===== ====== #
# ===== android ===== #
# ====== ===== ====== #

# firefox-esr | firefox
make_android= bash bash/android/gradle_build.sh # gradle_build_run.sh
target_android="build/zoxel.apk"

android:
	$(make_android)

android-run:
	bash bash/android/gradle_run.sh

android-sign:
	bash bash/android/gradle_sign.sh

android-install:
	bash bash/android/gradle_install.sh

android-install-run:
	bash bash/android/gradle_install.sh
	bash bash/android/gradle_run.sh

android-debug:
	bash bash/android/debug_android.sh

android-dev:
	bash bash/android/gradle_build_dev.sh

android-create-key:
	bash bash/android/generate_keystore.sh

android-uninstall:
	bash bash/android/gradle_uninstall.sh

android-clean:
	bash bash/android/gradle_clean.sh

android-update-settings:
	bash bash/android/copy_settings.sh

android-dev-debug:
	bash bash/android/install_debug.sh
	bash bash/android/debug_android.sh

install-android-sdk:
	bash bash/util/install_required_android.sh


# ==== ===== ==== #
# ===== all ===== #
# ==== ===== ==== #

# builds for all platforms - this rebuilds everytime tho
all: $(SRCS)
	@echo " > making all"
	@echo "   > making flecs [$(flecs_target)]"
	$(make_flecs_big)
	@echo "   > making flecs [$(target)]"
	$(make_release)
	@echo "   > making dev [$(target_dev)]"
	$(make_dev)
	@echo "   > making windows [$(target_windows)]"
	$(make_windows)
	@echo "   > making android [$(target_android)]"
	$(make_android)
	@echo "   > making web [$(target_web)]"
	$(make_web)
	@echo " > completed all"



# ==== ====== ==== #
# ===== util ===== #
# ==== ====== ==== #

# removes all build files
# todo: remove build, lib, include from project
clean:
	@echo "Cleaning All Build Files"
	bash bash/flecs/remove_flecs.sh

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


# ====== ======= ====== #
# ===== git & ssh ===== #
# ====== ======= ====== #

git-keys:
	bash bash/ssh/create_ssh.sh

git-push: ## installs zoxel into /usr/games directory
	bash bash/git/git_update_config.sh
	bash bash/git/git_push.sh

git-pull: ## installs zoxel into /usr/games directory
	bash bash/git/git_pull.sh

git-config:
	bash bash/git/git_update_config.sh

# ===== ===== ===== #
# ===== steam ===== #
# ===== ===== ===== #

# todo: use windows-steam directory
steam_libs = -Iinclude/steam -lsteam_wrapper -Wl,-rpath,'lib:../lib' -Dzox_include_steam
steam_objs = bash/steam/steamwrapper.c
make_linux_with_steam = $(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $(target) $(OBJS) $(steam_objs) $(LDLIBS) $(steam_libs) -lsteam_api
make_windows_with_steam = $(cc_windows) $(OBJS) include/flecs/flecs.c $(steam_objs) -o $(target_windows) $(windows_pre_libs) $(windows_includes) $(windows_libs) $(steam_libs) -lsteam_api64

steam-wrapper-linux:s
	bash bash/steam/build_wrapper.sh

steam-linux:
	@echo "	> building linux-steam"
	bash bash/steam/build_wrapper.sh
	@echo "    > copyin libsteam_api.so into build/linux"
	cp lib/libsteam_api.so build/linux/libsteam_api.so
	@echo "    > copyin libsteam_wrapper.so into build/linux"
	cp lib/libsteam_wrapper.so build/linux/libsteam_wrapper.so
	@echo " > building linux with steam"
	$(make_linux_with_steam) $(steam_libs) -Dzox_include_steam

steam-wrapper-windows:
	bash bash/steam/build_wrapper_windows.sh

steam-windows:
	@echo "	> building windows-steam"
	bash bash/steam/build_wrapper_windows.sh
	@echo "    > copyin lib/steam_api64.dll into build/windows"
	cp lib/steam_api64.dll build/windows/steam_api64.dll
	@echo "    > copyin lib/libsteam_wrapper.dll into build/windows"
	cp lib/libsteam_wrapper.dll build/windows/libsteam_wrapper.dll
	@echo " > building windows with steam"
	$(make_windows_with_steam)

steam-all:
	@echo "	> 1 building linux"
	bash bash/steam/build_wrapper.sh
	@echo "    > copyin libsteam_api.so into build/linux"
	cp lib/libsteam_api.so build/linux/libsteam_api.so
	@echo "    > copyin libsteam_wrapper.so into build/linux"
	cp lib/libsteam_wrapper.so build/linux/libsteam_wrapper.so
	$(make_linux_with_steam) $(steam_libs) -Dzox_include_steam
	@echo "	> 2 building windows"
	bash bash/steam/build_wrapper_windows.sh
	@echo "    > copyin lib/steam_api64.dll into build/windows"
	cp lib/steam_api64.dll build/windows/steam_api64.dll
	@echo "    > copyin lib/libsteam_wrapper.dll into build/windows"
	cp lib/libsteam_wrapper.dll build/windows/libsteam_wrapper.dll
	$(make_windows_with_steam)
	@echo "	> 3 packaging"
	bash bash/steam/package.sh
	@echo "	> 4 upload build/steam_export.zip"
	bash bash/steam/upload_package.sh
	# bash bash/steam/upload_package.sh --default

steam-sdk:
	bash bash/steam/install_sdk.sh

steam-package:
	bash bash/steam/package.sh

steam-upload:
	bash bash/steam/upload_package.sh

steam-upload-live:
	bash bash/steam/upload_package.sh --default

# install libs needed on steamdeck for builds there (steam os)
install-steam-deck-required:
	bash bash/steam/install_on_steam_deck.sh

# ===== ====== ===== #
# ===== itchio ===== #
# ===== ====== ===== #

itch-all:
	@echo "	> build linux"
	$(make_release)
	@echo "	> build windows"
	$(make_windows)
	@echo "	> upload all to itch io"
	bash bash/itch/upload.sh
	@echo "	> itch all complete"

itch-upload:
	bash bash/itch/upload.sh

itch-sdk:
	bash bash/itch/install_butler.sh


# ====== ======== ====== #
# ===== lost souls ===== #
# ====== ======== ====== #

help:
	@echo "zoxel -> an open source voxel engine"
	@echo "	latest @ https://codeberg.org/deus/zoxel"
	@echo "  > [linux]"
	@echo "  make <target>"
	@echo "    play			runs a play button"
	@echo "    install-play		installs a play button"
	@echo "    $(target_dev)			builds development"
	@echo "    <empty>  			builds release"
	@echo "    run				runs $(target)"
	@echo "    run-vulkan			runs $(target) with vulkan"
	@echo "    run-profiler		runs $(target) --profiler"
	@echo "    run-dev			runs $(target_dev)"
	@echo "    run-dev-debug		runs valgrind $(target_dev)"
	@echo "    run-dev-profiler		runs $(target_dev) --profiler"
	@echo "  > [web]"
	@echo "    web-sdk			installs tools for web build"
	@echo "    $(target_web)		builds zoxel-web"
	@echo "    run-web			runs $(target_web)"
	@echo "  > [android]"
	@echo "    install-android-sdk		installs tools for android build"
	@echo "    android			builds & runs android release"
	@echo "    android-create-key		created android keystore"
	@echo "    android-sign			signs the unsigned zoxel apk"
	@echo "    android-install		installs zoxel apk"
	@echo "    android-run			runs the zoxel apk"
	@echo "    android-dev			builds & runs android debug"
	@echo "    android-dev-debug		builds & runs android debug with logcat"
	@echo "    debug-android		debugs running android game"
	@echo "  > [setup]"
	@echo "    make $(flecs_target)	builds flecs"
	@echo "    install-required		installs required libraries for debian systems"
	@echo "    install-sdl			installs sdl"
	@echo "    install			installs zoxel"
	@echo "    uninstall			inuninstalls zoxel"
	@echo "    clean			removes all build files"
	@echo "  > [util]"
	@echo "    count			counts total lines in all source"
	@echo "    list-systems		lists all found zoxel systems in a module"
	@echo "    create-system		creates a new system in a module"
	@echo "    zip-build			zips zoxel build and resources"
	@echo "    github			opens zoxel on github"
	@echo "    codeberg			opens zoxel on codeberg"
	@echo "  > [flecs]"
	@echo "    check-flecs			checks flecs releases"
	@echo "    install-flecs		installs latest flecs (3.2.6)"
	@echo "    build/libflecs.a		builds flecs library"
	@echo "    remove-flecs		removes flecs library"
	@echo "    get-flecs-version		get a flecs by version"
	@echo "    get-nightly-flecs		gets latest flecs"
	@echo "  > [git]"
	@echo "    git-pull			pulls latest git"
	@echo "    git-push			pushes git updates (requires ssh access)"
	@echo "    git-keys			creates a ssh key to add to git servers"
	@echo "  > [windows]"
	@echo "    windows-sdk			installs tools for windows cross compilation"
	@echo "    build/zoxel.exe		builds windows release"
	@echo "  > [steam]"
	@echo "    steam-all			builds both wrappers, builds and uploads them to beta"
	@echo "    steam-wrapper-linux		builds steam wrapper lib/libsteam_wrapper.so"
	@echo "    steam-linux			builds zoxel-linux with steam added"
	@echo "    steam-wrapper-windows	builds steam wrapper lib/libsteam_wrapper.dll"
	@echo "    steam-windows		builds zoxel-windows with steam added"
	@echo "    steam-package		packages steam zip for upload"
	@echo "    steam-upload		uploads steam to beta branch"
	@echo "    steam-upload-live		uploads steam to main branch"
	@echo "    steam-sdk			installs steamworks sdk from zip ~/Downloads/steamworks_sdk.zip"
	@echo "    install-steam-deck-required	installs steamdeck required libs"
	@echo "  > [itchio]"
	@echo "    itch-all			builds all platforms uploads to itch"
	@echo "    itch-upload			uploads builds to itch"
	@echo "    itch-sdk			installs itch io butler"

# todo #

# todo: make default directory zoxel project instead of zoxel/build
# todo: clean more
# todo: create linux folder, and copy resources into it, for build step
# todo: make build folders per platform / build tags (for web and on window builds)
# todo: use a check for library and simply warn user here to make platform-sdk
# todo: integrate google services, for achievements, etc
# todo: integrate google play store uploads
# todo: for simple make, make a platform folder (linux or windows)
# todo: note whether x86 / arm for builds linux-x86_64, windows-x86_64, linux_arm64

# info on commands

# -D_DEFAULT_SOURCE Needed for a few functions, will be fixed in the future
# CFLAGS += -Wno-stringop-overflow-size
# for math.h, threading
# -Ofast Optimization Level | -Ofast | -O1 | -O2 | -O3
# -D NDEBUG No Debugging
# -s strip - removes 70kb atm
# -Wall Warnings, -gDebugging Info

# -fPIC Position Independent Code https://stackoverflow.com/questions/5311515/gcc-fpic-option
# ignore resources directory and gitignore in build?
# $(RM) build/*.o
# used to remove web?
# $(RM) $(target_web)
# $(RM) $(web_wasm_file)
# $(RM) $(web_data_file)
# $(RM) $(target)
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
# ldlibs_web += -L./ -lflecs
# halp - -lopengl32 doesn't have the right functions
# 'strings libopengl32.a | grep glBind' to find some functions
# enable #define zox_sdl_import_file_only for windows build
#  strings /usr/x86_64-w64-mingw32/lib/libopengl32.a | grep glBind
# LDLIBS += -lvulkan # vulkan on linux
# LDLIBS += -lGLEW
# -lwayland-client
# IS_STEAMWORKS := true

# used to check flecs before build

#ifneq ($(SYSTEM),Windows)
#	bash bash/util/install_required.sh
#endif
# set -e ; \
	bash bash/flecs/check_flecs_lib_not_installed.sh && bash bash/flecs/check_flecs_source.sh && bash bash/flecs/download_flecs_source.sh && cp include/flecs/flecs.h include; \
	bash bash/flecs/check_flecs_lib_not_installed.sh && cd build && $(make_flecs) && $(make_flecs_lib) && cd .. && cp build/libflecs.a lib; \
	bash bash/flecs/check_flecs_lib.sh &&

# bash bash/flecs/check_flecs_lib.sh && cd build && $(make_release)
# compiler tools and flags #
# NAME := zoxel
# -Wl,-Bsymbolic # -Wl,-rpath-link,'./bin/' # :../bin


#ifneq ($(SYSTEM),Windows)
#	bash bash/util/install_dev_required.sh
#endif
#  --leak-check=full
