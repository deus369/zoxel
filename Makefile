# ==== ===== ==== #
# ===== zox ===== #
# ==== ===== ==== #

# todo: for linux, a full build - which doesn't rely on system sdl
	# for regular package, just use system sdl2s

# requires: [git] [make] && make prepare
# platforms [linux, windows, web, android]
# stores [steam, itch, google]
# make game=zixel for zoxel2D
resources_dir = resources
flecs_version := "3.2.6"
# library use
use_system_sdl := true
# used for apps
use_lib_sdl := true
# used for texture file processing
use_lib_sdl_image := true
# used for audio
use_lib_sdl_mixer := true
# enable for ttf font files
use_lib_ttf := false
# todo: use libsdl2-ttf-dev instead? sdl2 true type font
# enable to debug amd gpu
use_lib_amd := false
# make vulkan=1 for vulkan
use_lib_vulkan := false
# more
patient_cmd = echo " > please be patient :), lord deus [>,<]/)"
finish_cmd = echo " > we are done :), lord deus -[>,O]-"
make_libs = -Llib -Iinclude -Wl,-rpath='lib' # default paths
make_libs += -lm -lpthread -lflecs # default libraries
ifdef game
    make_libs +=-Dzox_game=$(game)
else
    game = zoxel
endif
ifndef ($(use_system_sdl))
    # make_libs += -Dzox_lib_sdl_direct # use this if compiled sdl from source
    make_libs += -Dzox_lib_sdl -lSDL2
    make_libs += -Dzox_lib_sdl_images -lSDL2_image
    make_libs += -Dzox_lib_sdl_mixer -lSDL2_mixer
else
ifeq ($(use_lib_sdl), true)
    make_libs += -Dzox_lib_sdl -Iinclude/sdl -lSDL2
endif
ifeq ($(use_lib_sdl_image), true)
    make_libs += -Dzox_lib_sdl_images -Iinclude/sdl_image -lSDL2_image
endif
ifeq ($(use_lib_sdl_mixer), true)
    make_libs += -Dzox_lib_sdl_mixer -Iinclude/sdl_mixer -lSDL2_mixer
endif
endif
ifeq ($(use_lib_vulkan), true)
    make_libs += -lvulkan -Dzox_include_vulkan # vulkan on linux
endif
ifeq ($(use_lib_ttf), true)
   make_libs += -lfreetype -Dzox_lib_ttf -Ibuild/freetype/freetype-2.13.2/include -I/usr/include/freetype2
endif
ifeq ($(use_lib_amd), true)
   make_libs +=  -lrocm_smi64 -Dzox_lib_amd
endif
# determine the operating system #
ifeq ($(OS),Windows_NT)
    SYSTEM := Windows
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
    # make_libs += -Lbin
    make_libs += -LSDL2main -Wl,-subsystem,windows -mwindows -lws2_32 # windows only
    make_libs += -lopengl32 -lglew32
    # windows pathing
    make_libs += -Ibuild/sdl/include -Ibuild/sdl_image/include -Ibuild/sdl_mixer/include
    make_libs += -Lbuild/sdl/lib/x64 -Lbuild/sdl_image/lib/x64 -Lbuild/sdl_mixer/lib/x64
    make_libs += -Iinclude/glew -Lbuild/glew/lib/Release/x64 # glew
else # linux
    SYSTEM := $(shell uname -s)
    SRCS := $(shell find src/ -type f \( -name "*.c" -o -name "*.h" \))
    make_libs += -lGL
endif
CC = gcc # c99 | gnu99
OBJS = src/main.c
# collect our source files #
cflags = -std=gnu99 -D_DEFAULT_SOURCE -fPIC -Dflecs_version=\"$(flecs_version)\"
# supresses flecs warning
cflags += -Wno-stringop-overread -Wno-stringop-overflow
# make faster for release builds
cflags_release = -Ofast -D NDEBUG -s
ifneq ($(SYSTEM),Windows)
cflags_release += -flto=auto # fuse linker plugin on linux only
endif
# target per build type
target = build/$(game)-linux/$(game)
ifeq ($(SYSTEM),Windows)
target = build/$(game)-windows/$(game).exe
endif

# ===== ===== ===== #
# ===== linux ===== #
# ===== ===== ===== #

.PHONY: linux prepare install uninstall resources debug-libs install-sdl

make_release = echo " > building for release" && \
	$(patient_cmd) && \
	$(CC) $(cflags) $(cflags_release) -o $(target) $(OBJS) $(make_libs) && \
	$(finish_cmd)

# .DEFAULT_GOAL := $(target)

$(target): $(SRCS)
	@ $(make_release)

# @ make prepare

linux:
	@ make prepare
	@ $(make_release)

debug-make:
	@ echo '$(make_release)'

refresh-flecs:
	@ make -f make/flecs remove-flecs
	@ bash bash/flecs/download_flecs_source.sh "$(flecs_version)"
	# @ make -f make/flecs download-flecs
	@ make -f make/flecs flecs

# required libraries
prepare:
	@ make -f make/flecs download-flecs && make -f make/flecs flecs
ifeq ($(OS),Windows_NT) # on windows
	@ bash bash/windows/prepare.sh
else # linux
	@ bash bash/linux/prepare_minimal.sh $(game)
endif
zixel:
	@ echo "making [zixel]"
	@ make prepare game=zixel
	@ make game=zixel

# ===== ===== ===== #
# =====  run  ===== #
# ===== ===== ===== #

.PHONY: run run-debug-libs run-debug run-coop run-headless run-server run-tiny run-medium run-large run-vulkan

# run release
run:
	@ ./$(target) $(args)

run-debug-libs:
	LD_DEBUG=libs ./$(target)

run-server:
	@ ./$(target) --headless --server

run-client:
	@ ./$(target) --headless --client

run-coop:
	@ ./$(target) -s

run-headless:
	@ ./$(target) --headless

run-vulkan:
	@ ./$(target) --vulkan


# ====== ======= ====== #
# ===== linux dev ===== #
# ====== ======= ====== #

target_dev = build/$(game)-linux/$(game)
ifeq ($(SYSTEM),Windows)
target_dev = build/$(game)-windows/$(game).exe
endif
cflags_debug = -Wall -g # -O0 -fsanitize=address # -Wextra -Wpedantic -Wshadow -Wl,--verbose -Og
# cflags_debug += -fno-inline -fno-omit-frame-pointer
make_dev = echo " > building $(game)-linux [$(target_dev)]" && \
	$(patient_cmd) && \
	$(CC) $(cflags) $(cflags_debug) -o $(target_dev) $(OBJS) $(make_libs)

# development

$(target_dev): $(SRCS)
	@ $(make_dev)

dev:
	@ make $(target_dev)

run-dev:
	@ ./$(target_dev) $(args)

install-required-dev:
	@ bash bash/util/install_dev_required.sh

run-dev-headless:
	@ ./$(target_dev) --headless

run-dev-server:
	@ ./$(target_dev) --headless --server

run-dev-debug:
	@ gdb ./$(target_dev)

run-dev-debug-tiny:
	@ gdb --args ./$(target_dev) --tiny

gdb:
	@ echo "> running gdb with args [$(args)]"
	@ gdb ./$(target_dev) $(args)

# run development + valgrind  --tool=none
valgrind:
	@ echo "> running valgrind with args [$(args)]"
	@ valgrind ./$(target_dev) $(args)

run-drmemory:
	@ drmemory -light -callstack_max_frames 32 -malloc_max_frames 32  -- $(target_dev) $(args)

# -batch -quiet -light -no_text_output
# -batch -no_count_leaks  -no_track_allocs
#  -brief -light .exe  -batch -callstack_max_frames 16

run-drmemory-full:
	@ drmemory.exe -- $(target_dev) $(args)

run-coop-valgrind:
	@ valgrind ./$(target_dev) --tiny -s



run-drmemory-headless:
	@ drmemory.exe -brief -light $(PWD)/$(target_dev) --headless



.PHONY: dev run-dev run-drmemory

# with profiler
# build with profiler
profiler:
	@ echo " > building zoxel-linux with profiler"
	@ $(patient_cmd)
	@ $(make_dev) -Dzox_using_profiler

# run development + flecs profiler
run-profiler:
	@ echo "opening https://www.flecs.dev/explorer"
	@ sleep 3 && open https://www.flecs.dev/explorer &
	@ ./$(target_dev) $(args) --profiler

.PHONY: profiler run-profiler

# ==== ===== ==== #
# ===== all ===== #
# ==== ===== ==== #

.PHONY: all clean

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


# ====== ======== ====== #
# ===== lost souls ===== #
# ====== ======== ====== #

.PHONY: help help-flecs help-git help-debug help-steam help-itch help-web help-android help-extra help-analyse

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
	@echo " > [ls make]			see other makes"
	@echo " > [make -f make/<file>]	use more functions"
	@echo " - game is at [$(target)]"
	@echo " + to run, add args=<game_arguments>"
	@echo " + [make run args=--help] for in game arguments"
	@echo ""
	@echo " > make commands"
	@echo "  + make prepare		prepare build directory and libraries"
	@echo "  + make 			builds release into $(target)"
	@echo "  + make dev			builds development"
	@echo "  + make run			runs release build"
	@echo "  + make update			pulls latest with git and rebuilds"
	@echo "  + make resources		updates build resources"
	@echo "  + run-profiler		runs $(target) --profiler"
	@echo "  + run-dev			runs $(target_dev)"
	@echo "  + run-dev-debug		runs valgrind $(target_dev)"
	@echo "  + run-dev-profiler		runs $(target_dev) --profiler"

android:
	@ echo " > building zoxel-android"
	@ make -f make/android android

push:
	@ make -f make/git push

keys:
	@ make -f make/git keys

git-push:
	@ echo "!!! Use make push!"

.DEFAULT:
	@ echo " ! Unknown target '$@'"
	@ make help;
