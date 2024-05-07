# ==== ===== ==== #
# ===== zox ===== #
# ==== ===== ==== #

# requires: [git] [make] && make prepare
# platforms [linux, windows, web, android]
# stores [steam, itch, google]
# make game=zixel for zoxel2D
# library use
use_lib_sdl := true
use_lib_sdl_image := true
use_lib_sdl_mixer := true
use_lib_vulkan := false		# make vulkan=1 for vulkan
use_lib_ttf := true
resources_dir = resources

# more
patient_cmd = echo " > please be patient :), lord deus [>,<]/)"
LDLIBS = -lm -lpthread -lflecs -Llib # default libraries
ifdef game
    LDLIBS +=-Dzox_game=$(game)
endif
ifeq ($(use_lib_sdl), true)
    LDLIBS += -lSDL2
endif
ifeq ($(use_lib_sdl_image), true)
    LDLIBS += -lSDL2_image -Dzox_using_sdl_images
endif
ifeq ($(use_lib_sdl_mixer), true)
    LDLIBS += -lSDL2_mixer
endif
ifeq ($(use_lib_vulkan), true)
    LDLIBS += -lvulkan -Dzox_include_vulkan # vulkan on linux
endif
ifeq ($(use_lib_ttf), true)
   LDLIBS += -lfreetype -Dzox_lib_ttf -I/usr/include/freetype2/ # todo: make static for windows / test on windows
endif
# determine the operating system #
ifeq ($(OS),Windows_NT)
    SYSTEM := Windows
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
    # LDLIBS += -Lbin
    LDLIBS += -LSDL2main -Wl,-subsystem,windows -mwindows -lws2_32 # windows only
    LDLIBS += -lopengl32 -lglew32
    # windows pathing
    LDLIBS += -Ibuild/sdl/include -Ibuild/sdl_image/include -Ibuild/sdl_mixer/include
    LDLIBS += -Lbuild/sdl/lib/x64 -Lbuild/sdl_image/lib/x64 -Lbuild/sdl_mixer/lib/x64
    LDLIBS += -Ibuild/glew/include -Lbuild/glew/lib/Release/x64 # glew
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
target = build/windows/zoxel.exe
endif
CFLAGS_RELEASE = -Ofast -D NDEBUG -s
ifneq ($(SYSTEM),Windows)
CFLAGS_RELEASE += -flto=auto # fuse linker plugin on linux only
endif
make_release = $(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $(target) $(OBJS) $(LDLIBS)

$(target): $(SRCS)
	@ echo " > building zoxel-linux"
	@ $(patient_cmd)
	@ $(make_release)

linux:
	@ echo " > building zoxel-linux"
	@ $(patient_cmd)
	@ $(make_release)

# required libraries
prepare:
ifeq ($(OS),Windows_NT) # on windows
	@ bash bash/windows/prepare.sh
else # linux
	@ bash bash/linux/prepare.sh
endif
	@ make install-flecs && make build/libflecs.a

#install-required:
#	@ bash bash/util/install_required.sh

## installs zoxel into /usr/games directory
install: 
ifeq ($(OS),Windows_NT) # on windows
	@ bash bash/windows/install.sh
else # linux
	@ bash bash/install/install.sh
endif

## uninstalls zoxel into /usr/games directory
uninstall: 
	@ bash bash/install/uninstall.sh

# run release
run:
	@ ./$(target)

run-coop:
	@ ./$(target) -s

run-headless:
	@ ./$(target) --headless

run-server:
	@ ./$(target) --headless --server

run-tiny:
	@ ./$(target) --tiny

run-medium:
	@ ./$(target) --medium

run-large:
	@ ./$(target) --large

run-vulkan:
	@ ./$(target) --vulkan


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
	@ echo " > building zoxel-dev-linux"
	@ $(patient_cmd)
	@ $(make_dev)

$(target_dev): $(SRCS)
	@ echo " > building zoxel-dev-linux"
	@ $(patient_cmd)
	@ $(make_dev)

run-dev:
	@ ./$(target_dev)

run-dev-headless:
	@ ./$(target_dev) --headless

run-dev-server:
	@ ./$(target_dev) --headless --server

run-dev-tiny:
	@ ./$(target_dev) --tiny

run-dev-vulkan:
	@ ./$(target_dev) --vulkan

run-debug-vulkan:
	@ echo " > running gdb with vulkan"
	@ $(patient_cmd)
	@ valgrind ./$(target_dev) --vulkan

run-debug:
	@ gdb ./$(target_dev)

# run development + valgrind
run-valgrind:
	@ valgrind ./$(target_dev)

# run release + flecs profiler
run-profiler:
	@ sleep 3 && open https://www.flecs.dev/explorer &
	@ ./$(target) --profiler

# run development + flecs profiler
run-dev-profiler:
	@ sleep 3 && open https://www.flecs.dev/explorer &
	@ ./$(target_dev) --profiler

run-dev-profiler-tiny:
	@ sleep 3 && open https://www.flecs.dev/explorer &
	@ ./$(target_dev) --profiler --tiny

run-dev-debug-tiny:
	@ valgrind -s ./$(target_dev) --tiny


# ===== ===== ===== #
# ===== flecs ===== #
# ===== ===== ===== #

flecs_target = build/libflecs.a
flecs_source = include/flecs/flecs.c
flecs_lib = lib/libflecs.a
flecs_flags = -c
flecs_obj = build/flecs.o
flecs_libs = -lm -lpthread
ifeq ($(SYSTEM), Windows) # win sockets
flecs_libs += -lws2_32
endif
make_flecs = $(CC) $(flecs_flags) $(CFLAGS) $(CFLAGS_RELEASE) $(flecs_source) -o $(flecs_obj) $(flecs_libs)
make_flecs_lib = ar rcs $(flecs_target) $(flecs_obj)
make_flecs_big= set -e; \
	$(make_flecs) && \
	$(make_flecs_lib) && \
	rm $flecs_obj && \
	cp $flecs_target $flecs_lib

# bash bash/flecs/check_flecs_source.sh && bash bash/flecs/download_flecs_source.sh && \

# downloads source into include, installs library into lib
$(flecs_target):
	@ $(make_flecs_big)

flecs:
	@ $(make_flecs_big)

install-sdl:
	@ bash bash/sdl/install_sdl.sh

install-flecs:
	@ bash bash/flecs/download_flecs_source.sh

# @ bash bash/flecs/remove_flecs.sh

remove-flecs:
	@ bash bash/flecs/remove_flecs.sh

get-nightly-flecs:
	@ bash bash/flecs/nightly_flecs.sh

get-flecs-version:
	@ bash bash/flecs/download_flecs_version.sh

revert-nightly-flecs:
	@ bash bash/flecs/nightly_revert_source.sh

check-flecs:
	@ open https://github.com/SanderMertens/flecs/releases &

# ====== ===== ====== #
# ===== windows ===== #
# ====== ===== ====== #
# [from linux]

cc_windows=x86_64-w64-mingw32-gcc # -Wall -g
target_windows = build/windows/zoxel.exe
windows_pre_libs = -Llib
windows_libs = -lm -lpthread
windows_libs += -Wl,-subsystem,windows -mwindows -lws2_32 # windows only
windows_libs += -lopengl32 -lglew32
# more sdl2
windows_libs += -LSDL2main -lSDL2
ifeq ($(use_lib_sdl_image), true)
	windows_libs += -lSDL2_image
endif
ifeq ($(use_lib_sdl_mixer), true)
    windows_libs += -lSDL2_mixer
endif
# windows pathing
windows_includes = -Iinclude #  -I/usr/include/SDL2 -I/usr/include/GL
# -Lbuild/sdl/sdl/build/.libs -Lbuild/sdl/sdl_mixer/build/.libs -Lbuild/sdl/sdl_image/.libs
windows_includes += -Ibuild/sdl/include -Ibuild/sdl_image/include -Ibuild/sdl_mixer/include
windows_includes += -Lbuild/sdl/lib/x64 -Lbuild/sdl_image/lib/x64 -Lbuild/sdl_mixer/lib/x64
windows_includes += -Ibuild/glew/include -Lbuild/glew/lib/Release/x64 # glew
# command
make_windows = $(cc_windows) $(CFLAGS) $(CFLAGS_RELEASE) $(OBJS) include/flecs/flecs.c -o $(target_windows) $(windows_pre_libs) $(windows_includes) $(windows_libs) --static # this fixes thread dll issue

# todo: copy resources and bin dll's into the folder build/windows
ifneq ($(SYSTEM),Windows)

$(target_windows): $(SRCS)
	@ echo " > building zoxel-windows"
	@ $(patient_cmd)
	@ $(make_windows)

windows:
	@ echo " > building zoxel-windows"
	@ $(patient_cmd)
	@ if [ ! -d build/windows ]; then mkdir build/windows; fi
	@ $(make_windows)

endif

# @ WINEPATH=bin wine $(target_windows)

run-windows:
	@ WINEPREFIX=~/.wine64 wine $(target_windows)

run-windows-debug:
	@ WINEPREFIX=~/.wine64 WINEDEBUG=+backtrace wine $(target_windows)

# @ WINEPREFIX=~/.wine64 WINEDEBUG=+all wine $(target_windows)
# @ WINEPREFIX=~/.wine64 WINEDEBUG=+opengl wine $(target_windows)

prepare-windows: # for linux cross platform build
	@ echo " > preparing windows"
	@ $(patient_cmd)
	@ make install-flecs && make build/libflecs.a
	@ bash bash/windows/install_sdk.sh
	@ bash bash/windows/prepare.sh

# ======= ===== ======= #
# ===== windows32 ===== #
# ======= ===== ======= #

cc_windows_32=i686-w64-mingw32-gcc
target_windows_32 = build/windows_32/zoxel_32.exe

# todo: windows 32 build, linux32, etc

# ==== ===== ==== #
# ===== web ===== #
# ==== ===== ==== #

cc_web = build/emsdk/upstream/emscripten/emcc
emrun=build/emsdk/upstream/emscripten/emrun
emsdk=python3 build/emsdk/emsdk.py
target_web_dir = build/web
target_web = $(target_web_dir)/zoxel.html # .js
web_wasm_file = $(target_web_dir)/zoxel.wasm
web_data_file = $(target_web_dir)/zoxel.data
make_web_checks= [ ! -d $(target_web_dir) ] && mkdir -p $(target_web_dir); \
[ ! -d $(target_web_dir)/resources ] && cp -R $(resources_dir) $(target_web_dir)/resources;
web_resources_dir = -Dresources_dir_name="\"resources\""
cflags_web = --preload-file $(resources_dir) -s WASM=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s ALLOW_MEMORY_GROWTH -s STACK_SIZE=365536 -s EXPORTED_FUNCTIONS=['_main','_ntohs']
ldlibs_web = -lGL -lGLEW -lSDL -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_MIXER=2
make_web = $(make_web_checks) $(emsdk) construct_env && $(cc_web) $(CFLAGS) $(cflags_web) $(web_resources_dir) -o $(target_web) $(OBJS) include/flecs/flecs.c $(ldlibs_web) && bash bash/web/post_build.sh

prepare-web:
	@ bash bash/web/prepare.sh

$(target_web): $(SRCS)
	@ echo " > building zoxel-web"
	@ $(patient_cmd)
	@ $(make_web)

web:
	@ echo " > building zoxel-web"
	@ $(patient_cmd)
	@ $(make_web)

# Runs zoxel web release build
run-web:
	$(emrun) $(target_web)

# ~/projects/emsdk/upstream/emscripten/emrun --browser firefox zoxel.html

# todo: download zoxel-play for web live on git

# updates the zoxel-play project
update-web:
	@ bash bash/web/update_zoxel_play.sh

# updates the zoxel-play project
run-zoxel-play:
	@ bash bash/web/run_zoxel_play.sh

# updates the zoxel-play project
git-push-zoxel-play:
	@ echo " > pushing from projects/zoxel-play"
	@ cd ../zoxel-play && bash/git/git_push.sh

# ====== ===== ====== #
# ===== android ===== #
# ====== ===== ====== #

# firefox-esr | firefox
make_android = bash bash/android/gradle_build_release.sh # gradle_build_run.sh
target_android = build/zoxel.apk

prepare-android:
	@ echo " > preparing for android"
	@ $(patient_cmd)
	@ bash bash/android/prepare.sh

prepare-android-emu:
	@ echo " > installing android emulator"
	@ $(patient_cmd)
	@ bash bash/android/prepare_emu.sh

android:
	@ echo " > building zoxel-android"
	@ $(patient_cmd)
	@ $(make_android)

android-push:
	@ echo " > installing and running zoxel.apk"
	@ $(patient_cmd)
	@ bash bash/android/gradle_push_release.sh

android-sdl:
	@ echo " > installing sdl for android"
	@ $(patient_cmd)
	@ bash bash/android/install_sdl.sh
	@ bash bash/android/copy_sdl.sh

android-clean:
	@ echo " > cleaning up android build files"
	@ $(patient_cmd)
	@ bash bash/android/clean_sdk.sh

# @ bash bash/android/gradle_install.sh && bash bash/android/gradle_run.sh

android-install:
	@ bash bash/android/gradle_install.sh

android-run:
	@ bash bash/android/gradle_run.sh

android-sign:
	@ bash bash/android/gradle_sign.sh

android-debug:
	@ bash bash/android/debug_android.sh

android-dev:
	@ bash bash/android/gradle_build_dev.sh

android-create-key:
	@ bash bash/android/generate_keystore.sh

android-uninstall:
	@ bash bash/android/gradle_uninstall.sh

#android-clean:
#	bash bash/android/gradle_clean.sh

android-update-settings:
	@ bash bash/android/copy_settings.sh

android-dev-debug:
	@ bash bash/android/install_debug.sh
	@ bash bash/android/debug_android.sh


# ====== ======= ====== #
# ===== git & ssh ===== #
# ====== ======= ====== #

ssh:
	@ bash bash/ssh/create_ssh.sh

git-push: ## installs zoxel into /usr/games directory
	@ bash bash/git/git_update_config.sh
	@ bash bash/git/git_push.sh

git-commit: ## creates a commit in terminal
	@ echo create a commit  pusher script

git-push-only: ## pushes commit, created otherwise
	@ bash bash/git/git_push_only.sh

git-pull: ## installs zoxel into /usr/games directory
	@ bash bash/git/git_pull.sh

git-config:
	@ bash bash/git/git_update_config.sh

update: ## installs zoxel into /usr/games directory
	@ echo " + updating zoxel"
	@ bash bash/git/git_pull.sh
	@ bash make prepare && make && make install

# ===== ===== ===== #
# ===== steam ===== #
# ===== ===== ===== #

# todo: use windows-steam directory
steam_libs = -Iinclude/steam -lsteam_wrapper -Wl,-rpath,'lib:../lib' -Dzox_include_steam
steam_objs = bash/steam/steamwrapper.c
make_linux_with_steam = $(CC) $(CFLAGS) $(CFLAGS_RELEASE) -o $(target) $(OBJS) $(steam_objs) $(LDLIBS) $(steam_libs) -lsteam_api
make_windows_with_steam = $(cc_windows) $(OBJS) include/flecs/flecs.c $(steam_objs) -o $(target_windows) $(windows_pre_libs) $(windows_includes) $(windows_libs) $(steam_libs) -lsteam_api64

steam-wrapper-linux:
	@ bash bash/steam/build_wrapper_linux.sh

steam-wrapper-windows:
	@ bash bash/steam/build_wrapper_windows.sh

steam-linux:
	@ echo " > building linux-steam wrapper"
	@ bash bash/steam/build_wrapper_linux.sh
	@ echo " > building linux-steam"
	@ $(patient_cmd)
	@ $(make_linux_with_steam)

steam-windows:
	@ echo " > building windows-steam wrapper"
	@ bash bash/steam/build_wrapper_windows.sh
	@ echo " > building windows-steam"
	@ $(patient_cmd)
	@ $(make_windows_with_steam)

steam-all:
	@ echo " > [1/6] building linux-steam wrapper"
	@ bash bash/steam/build_wrapper_linux.sh
	@ echo " > [2/6] building linux-steam"
	@ $(make_linux_with_steam)
	@ echo " > [3/6] building windows-steam wrapper"
	@ bash bash/steam/build_wrapper_windows.sh
	@ echo " > [4/6] building windows-steam"
	@ $(make_windows_with_steam)
	@ echo " > [5/6] packaging build/steam_export.zip"
	@ bash bash/steam/package.sh
	@ echo " > [6/6] uploading build/steam_export.zip"
	@ $(patient_cmd)
	@ bash bash/steam/upload_package.sh
	# bash bash/steam/upload_package.sh --default

steam-sdk:
	@ bash bash/steam/install_sdk.sh

steam-package:
	@ bash bash/steam/package.sh

steam-upload:
	@ bash bash/steam/upload_package.sh

steam-upload-live:
	@ bash bash/steam/upload_package.sh --default

# install libs needed on steamdeck for builds there (steam os)
install-steam-deck-required:
	@ bash bash/steam/install_on_steam_deck.sh

clean-steam:
	@ echo " > cleaning steam builds"
	@ bash bash/steam/clean.sh

# ===== ====== ===== #
# ===== itchio ===== #
# ===== ====== ===== #

itch-all:
	@ echo "	> build linux"
	@ $(make_release)
	@ echo "	> build windows"
	@ $(make_windows)
	@ echo "	> upload all to itch io"
	@ bash bash/itch/upload.sh
	@ echo "	> itch all complete"

itch-upload:
	@ bash bash/itch/upload.sh

itch-sdk:
	@ bash bash/itch/install_butler.sh


# ==== ===== ==== #
# ===== all ===== #
# ==== ===== ==== #

# builds for all platforms - this rebuilds everytime tho
all: $(SRCS)
	@ echo " > making all"
	@ echo "  > making flecs [$(flecs_target)]"
	@ $(make_flecs_big)
	@ echo "  > making flecs [$(target)]"
	@ $(make_release)
	@ echo "  > making dev [$(target_dev)]"
	@ $(make_dev)
	@ echo "   > making windows [$(target_windows)]"
	@ $(make_windows)
	@ echo "   > making android [$(target_android)]"
	@ $(make_android)
	@ echo "   > making web [$(target_web)]"
	@ $(make_web)
	@ echo " > completed all builds"

# clean all things
clean:
	@ bash bash/util/clean.sh

# @echo " > cleaning flecs"
# bash bash/flecs/remove_flecs.sh


# ==== ====== ==== #
# ===== util ===== #
# ==== ====== ==== #

# removes all build files
# todo: remove build, lib, include from project

codeberg:
	@ open https://codeberg.org/deus/zoxel &

github:
	@ open https://github.com/deus369/zoxel &

create-system:
	@ bash bash/zoxel/create_system.sh

zip-build:
	@ bash bash/util/zip_build.sh

install-play:
	@ bash bash/install/install_play_button.sh

play:
	@ gcc tests/glut/play_button.c -o build/play_button -lglut -lGL -lGLU && ./build/play_button &



# -==== ====== ====- #
# ===== counts ===== #
# -==== ====== ====- #

count:
	@ echo " > counting source files"
	@ bash bash/count/count_source.sh

count-systems:
#	@ bash bash/count/count_systems.sh
	@ bash bash/count/create_systems_chart.sh

list-systems:
	@ echo " > listing systems"
	# @ bash bash/count/list_systems.sh
	@ bash bash/zoxel/list_systems.sh

#show-systems:
#	@ echo " > showing systems"
#	@ bash bash/count/create_systems_chart.sh

# ====== ======== ====== #
# ===== lost souls ===== #
# ====== ======== ====== #

help:
	@echo "  "
	@echo "welcome to [zoxel] help menu"
ifeq ($(OS),Windows_NT)
	@echo "   [you are on windows]"
else
	@echo "   [you are on [linux]"
endif
	@echo "   [@https://codeberg.org/deus/zoxel]"
	@echo "  "
	@echo " > make commands"
	@echo "  + make prepare	prepare build directory and libraries"
	@echo "  + make 		builds release into $(target)"
	@echo "  + make dev		builds development"
	@echo "  + make run		runs release build"
	@echo "  + make run-vulkan	runs release with vulkan"
	@echo "  + make update		pulls latest with git and rebuilds"
	@echo "  "
	@echo " > help-x commands"
	@echo "  + flecs		building flecs"
	@echo "  + extra		all the extras"
	@echo "  + git			git bash helpers"
	@echo "  + android-		android builds"
	@echo "  + web			web builds"
	@echo "  + steam		steam integration"
	@echo "  + itch		itch-io automation"
	@echo "  "

help-debug:
	@echo "    run-profiler		runs $(target) --profiler"
	@echo "    run-dev			runs $(target_dev)"
	@echo "    run-dev-debug		runs valgrind $(target_dev)"
	@echo "    run-dev-profiler		runs $(target_dev) --profiler"

help-flecs:
	@echo "  > [flecs]"
	@echo "    make $(flecs_target)	builds flecs"
	@echo "    check-flecs			checks flecs releases"
	@echo "    install-flecs		installs latest flecs (3.2.6)"
	@echo "    build/libflecs.a		builds flecs library"
	@echo "    remove-flecs		removes flecs library"
	@echo "    get-flecs-version		get a flecs by version"
	@echo "    get-nightly-flecs		gets latest flecs"

help-extra:
	@echo "  > [setup]"
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
	@echo "    play			runs a play button"
	@echo "    install-play		installs a play button"
	@echo "  > [linux-to-windows]"
	@echo "    make prepare-windows	prepare build directory and libraries"
	@echo "    windows-sdk			installs tools for windows cross compilation"
	@echo "    windows			builds windows release"

help-git:
	@echo "  > [git]"
	@echo "    git-pull			pulls latest git"
	@echo "    git-push			pushes git updates (requires ssh access)"
	@echo "    ssh				creates a ssh key to add to git servers"

help-android:
	@echo "  > [android]"
	@echo "    prepare-android		installs tools for android build"
	@echo "    prepare-android-emu		installs waydroid for local android"
	@echo "    android			builds & runs android release"
	@echo "    android-create-key		created android keystore"
	@echo "    android-sign		signs the unsigned zoxel apk"
	@echo "    android-install		installs zoxel apk"
	@echo "    android-run			runs the zoxel apk"
	@echo "    android-dev			builds & runs android debug"
	@echo "    android-dev-debug		builds & runs android debug with logcat"
	@echo "    debug-android		debugs running android game"

help-web:
	@echo "  > [web]"
	@echo "    prepare-web	installs tools for web build"
	@echo "    web		builds web [ $(target_web)]"
	@echo "    run-web	runs web"

help-steam:
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

help-itch:
	@echo "  > [itchio]"
	@echo "    itch-all			builds all platforms uploads to itch"
	@echo "    itch-upload			uploads builds to itch"
	@echo "    itch-sdk			installs itch io butler"
