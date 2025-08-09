# ==== Zoxel ====
# 	- remembers last picked game
# Choose your game module
LAST_GAME_FILE := .game

ifeq ($(origin game), undefined)
    ifeq ($(shell test -f $(LAST_GAME_FILE) && echo yes),)
        GAME := zoxel
    else
        GAME := $(shell cat $(LAST_GAME_FILE))
    endif
else
    GAME := $(game)
endif


SRC_DIR 	:= src
SRC    		:= src/main.c
SRCS 		:= $(shell find $(SRC_DIR) -name "*.c") # Change Detection
CC      	:= gcc

# 🧱 Release build — for speed and glory
# 03 breaks my sounds for now
CFLAGS      	:= -fPIC -O3 -march=native -flto=auto -DNDEBUG -Dzox_debug

# 🐛 Debug build — for truth and stacktraces
#	-g3 -g
CFLAGS_DEV 	:= -fPIC -O0 -g3 -Wall -ggdb3 -Dzox_debug \
			-Wextra -Wpedantic # -Werror

CFLAGS_DEV2  	:= -Dzox_debug -O0 -fPIC -g3 -Wall -Wextra -Werror \
			-fno-omit-frame-pointer -fdiagnostics-color=always \
			-std=c99 -D_POSIX_C_SOURCE=200809L

LDFLAGS 	:= -lflecs -lm -lpthread -lGL -lSDL2 -lSDL2_image -lSDL2_mixer \
			-Dzox_sdl -Dzox_sdl_mixer -Dzox_sdl_images \
			-Dzox_game=$(GAME)
TARGET  	:= bin/$(GAME)
TARGET_DEV 	:= bin/$(GAME)-debug
GAMES_DIR	:= $(SRC_DIR)/nexus

.PHONY: game help clean build dev pick run rund runp runpd gdb val

# Build

$(TARGET): $(SRCS)
	@ echo "> Building [$(GAME)]"
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)
	@ echo "-------------------"
	@ echo " - completed -"
	@ echo "-------------------"

build: $TARGET

# Extra

game:
	@ echo "> You are working on [$(GAME)]"

help:
	@ cat doc/help.md

clean:
	@ echo "> You are removing [bin dist]"
	@ rm -rf bin dist

# Dev

$(TARGET_DEV): $(SRCS)
	@ mkdir -p bin
	$(CC) $(CFLAGS_DEV) $(SRC) -o $@ $(LDFLAGS)

dev: $(TARGET_DEV)


# Run

run: $(TARGET)
	@ echo "> Running [$(GAME)]"
	@ sleep 1
	@ echo "-------------------"
	@ ./$(TARGET)

rund: dev
	./$(TARGET_DEV)

runv: dev
	./$(TARGET_DEV) --verbose

gdb: dev
	gdb -ex "set debuginfod enabled off" -ex run --args ./$(TARGET_DEV)

gdbv: dev
	gdb -ex "set debuginfod enabled off" -ex run --args ./$(TARGET_DEV) --verbose

val: dev
	valgrind ./$(TARGET_DEV)

gdbp:
	$(MAKE) pick ACTION=gdb

# Dep

flecs:
	cd ../flecsing && make clean && make download && make refresh



# Pick

ACTION ?= build

pick:
	@echo "Scanning the Games...";\
	i=1; \
	for d in $(GAMES_DIR)/*/; do \
		gamename=$$(echo $$d | sed 's|$(GAMES_DIR)/||; s|/$$||'); \
		echo "$$i) $$gamename"; \
		eval "game_$$i=$$gamename"; \
		i=$$((i + 1)); \
	done; \
	read -p "Pick a game by number: " choice; \
	selected_game=$$(eval echo \$$$$(echo game_$$choice)); \
	if [ -n "$$selected_game" ]; then \
		echo "$$selected_game" > $(LAST_GAME_FILE); \
		echo "You selected: $$selected_game $$ACTION"; \
		$(MAKE) game=$$selected_game $$ACTION; \
	else \
		echo "Invalid selection."; \
		exit 1; \
	fi

runp:
	$(MAKE) pick ACTION=run

runpd:
	$(MAKE) pick ACTION=rund