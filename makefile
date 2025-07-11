# ==== Zoxel ====

GAME    	:= zoxel
SRC_DIR 	:= src
SRC    		:= src/main.c
SRCS 		:= $(shell find $(SRC_DIR) -name "*.c")  # Recursive
TARGET  	:= bin/$(GAME)
TARGET_DEV 	:= bin/$(GAME)-debug
CC      	:= gcc
CFLAGS  	:= -O3 -fPIC
CFLAGS_DEV 	:= -O0 -fPIC -g -Wall -ggdb3 # -Wshadow -Wpedantic -fno-omit-frame-pointer
LDFLAGS 	:= -lm -lpthread -lflecs -lSDL2 -lSDL2_image -lSDL2_mixer -lGL
LDFLAGS 	+= -Dzox_lib_sdl -Dzox_lib_sdl_mixer -Dzox_lib_sdl_images

$(TARGET): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

$(TARGET_DEV): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS_DEV) $(INCLUDES) $(SRC) -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

dev: $(TARGET_DEV)

run-dev: dev
	./$(TARGET_DEV)

gdb: dev
	gdb ./$(TARGET_DEV)

valgrind: dev
	valgrind ./$(TARGET_DEV)

clean:
	rm -rf bin
	rm -rf dist

flecs:
	cd ../flecsing && make clean && make download && make refresh

.PHONY: all run dev run-dev run-gdb run-val clean

# catching memory errors >
# 	CFLAGS_DEV += -fsanitize=address,undefined
# catching leaks >
# 	CFLAGS_DEV += -fsanitize=address,leak -fno-omit-frame-pointer

VERSION      := 0.0.1
PACKAGE_DIR  := dist/$(GAME)_$(VERSION)
INSTALL_DIR  := $(PACKAGE_DIR)/usr/local/games/$(GAME)
BIN_DIR      := $(INSTALL_DIR)/bin
RES_DIR      := $(INSTALL_DIR)/res
DESKTOP_DIR  := $(PACKAGE_DIR)/usr/share/applications
CONTROL_DIR  := $(PACKAGE_DIR)/DEBIAN
ICON_DIR     := $(PACKAGE_DIR)/usr/share/icons/hicolor/64x64/apps
ICON_SRC     := res/textures/game_icon.png
ICON_DEST    := $(ICON_DIR)/$(GAME).png

package: $(TARGET)
	# Create required dirs
	mkdir -p $(CONTROL_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(RES_DIR)
	mkdir -p $(DESKTOP_DIR)
	mkdir -p $(ICON_DIR)

	# Copy binary
	cp $(TARGET) $(BIN_DIR)/$(GAME)
	chmod +x $(BIN_DIR)/$(GAME)

	# Copy resources (recursive)
	cp -r res/* $(RES_DIR)/ || true

	# Copy icon
	cp $(ICON_SRC) $(ICON_DEST)

	# Control file
	echo "Package: $(GAME)"                                  >  $(CONTROL_DIR)/control
	echo "Version: $(VERSION)"                              >> $(CONTROL_DIR)/control
	echo "Section: games"                                   >> $(CONTROL_DIR)/control
	echo "Priority: optional"                               >> $(CONTROL_DIR)/control
	echo "Architecture: amd64"                              >> $(CONTROL_DIR)/control
	echo "Maintainer: Deus <you@example.com>"               >> $(CONTROL_DIR)/control
	echo "Description: A procedurally-generated voxel RPG"  >> $(CONTROL_DIR)/control
	echo "Depends: libc6 (>= 2.31), libgl1, libsdl2-2.0-0, libsdl2-mixer-2.0-0, libsdl2-image-2.0-0, flecs (3.2.7)" >> $(CONTROL_DIR)/control

	# .desktop launcher
	echo "[Desktop Entry]"                              >  $(DESKTOP_DIR)/$(GAME).desktop
	echo "Name=Zoxel"                                   >> $(DESKTOP_DIR)/$(GAME).desktop
	echo "Exec=/usr/local/games/$(GAME)/bin/$(GAME)"    >> $(DESKTOP_DIR)/$(GAME).desktop
	echo "Icon=$(GAME)"                                 >> $(DESKTOP_DIR)/$(GAME).desktop
	echo "Type=Application"                             >> $(DESKTOP_DIR)/$(GAME).desktop
	echo "Categories=Game;"                             >> $(DESKTOP_DIR)/$(GAME).desktop

	# Build the .deb
	dpkg-deb --build $(PACKAGE_DIR)