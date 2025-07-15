# ==== Zoxel ====

GAME    	:= zoxel # todo: remember last picked game
SRC_DIR 	:= src
SRC    		:= src/main.c
SRCS 		:= $(shell find $(SRC_DIR) -name "*.c")  # Recursive
CC      	:= gcc
CFLAGS  	:= -O3 -fPIC
CFLAGS_DEV 	:= -O0 -fPIC -g -Wall -ggdb3 # -Wshadow -Wpedantic -fno-omit-frame-pointer
LDFLAGS 	:= -lm -lpthread -lflecs -lSDL2 -lSDL2_image -lSDL2_mixer -lGL
LDFLAGS 	+= -Dzox_lib_sdl -Dzox_lib_sdl_mixer -Dzox_lib_sdl_images
# Choose your game module
ifdef game
    LDFLAGS +=-Dzox_game=$(game)
    GAME := $(game)
endif
TARGET  	:= bin/$(GAME)
TARGET_DEV 	:= bin/$(GAME)-debug

.PHONY: all run dev rund gdb val clean package-deb package-pac package pick

# Our makes

$(TARGET): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

$(TARGET_DEV): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS_DEV) $(INCLUDES) $(SRC) -o $@ $(LDFLAGS)

build: $TARGET

dev: $(TARGET_DEV)

run: $(TARGET)
	./$(TARGET)

rund: dev
	./$(TARGET_DEV)

gdb: dev
	gdb ./$(TARGET_DEV)

val: dev
	valgrind ./$(TARGET_DEV)

clean:
	rm -rf bin
	rm -rf dist

flecs:
	cd ../flecsing && make clean && make download && make refresh

ACTION ?= build

pick:
	@echo "Scanning the nexus...";\
	i=1; \
	for d in src/nexus/*/; do \
		gamename=$$(echo $$d | sed 's|src/nexus/||; s|/$$||'); \
		echo "$$i) $$gamename"; \
		eval "game_$$i=$$gamename"; \
		i=$$((i + 1)); \
	done; \
	read -p "Pick a game by number: " choice; \
	selected_game=$$(eval echo \$$$$(echo game_$$choice)); \
	if [ -n "$$selected_game" ]; then \
		echo "You selected: $$selected_game"; \
		$(MAKE) game=$$selected_game $$ACTION; \
	else \
		echo "Invalid selection."; \
		exit 1; \
	fi

runp:
	$(MAKE) pick ACTION=run

# our packaging, move this to Zoxelder

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
PKGBUILD := $(PACKAGE_DIR)/PKGBUILD

package-deb: $(TARGET)
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


# Pacman package

package-pac: $(TARGET)
	@# 1. Prepare directory layout
	mkdir -p $(PACKAGE_DIR)/usr/share/games/$(GAME)/bin \
	         $(PACKAGE_DIR)/usr/share/games/$(GAME)/res

	@# 2. Copy executable and resources
	cp $(TARGET) $(PACKAGE_DIR)/usr/share/games/$(GAME)/bin/$(GAME)
	chmod +x $(PACKAGE_DIR)/usr/share/games/$(GAME)/bin/$(GAME)
	cp -r res/* $(PACKAGE_DIR)/usr/share/games/$(GAME)/res/ || true

	@# 3. Emit PKGBUILD line by line (no heredoc)
	@echo "pkgname=$(GAME)"                                                       >  $(PKGBUILD)
	@echo "pkgver=$(VERSION)"                                                     >> $(PKGBUILD)
	@echo "pkgrel=1"                                                              >> $(PKGBUILD)
	@echo "pkgdesc=\"A procedurally-generated voxel RPG\""                       >> $(PKGBUILD)
	@echo "arch=('x86_64')"                                                       >> $(PKGBUILD)
	@echo "depends=('sdl2' 'sdl2_image' 'sdl2_mixer' 'flecs')"                    >> $(PKGBUILD)
	@echo "source=(\"\$${srcdir}/$(TARGET)\" \"res/*\")"                         >> $(PKGBUILD)
	@echo "build() { return 0; }"                                                 >> $(PKGBUILD)
	@echo "package() {"                                                           >> $(PKGBUILD)
	@echo "  install -Dm755 \"\$${srcdir}/$(TARGET)\" \"\$${pkgdir}/usr/share/games/$(GAME)/bin/$(GAME)\"" \
	                                                                               >> $(PKGBUILD)
	@echo "  cp -r \"\$${srcdir}/res\" \"\$${pkgdir}/usr/share/games/$(GAME)/res/\"" >> $(PKGBUILD)
	@echo "}"                                                                     >> $(PKGBUILD)

	@# 4. Build the Arch package
	@(cd $(PACKAGE_DIR) && makepkg --force --noconfirm --packagetype pkg)

# Wrapper to auto‑select package format
package:
	@if command -v pacman >/dev/null; then \
		$(MAKE) package-pac; \
	elif command -v dpkg-deb >/dev/null; then \
		$(MAKE) package-deb; \
	else \
		echo "Unsupported packaging system."; exit 1; \
	fi

help:
	@printf "\n\033[1;30m⟡ Zoxel Build System ⟡\033[0m\n\n"
	@printf "  \033[38;5;208m▶ build\033[0m    Build release for $(GAME)\n"
	@printf "  \033[38;5;208m▶ dev\033[0m      Build debug\n"
	@printf "  \033[38;5;208m▶ run\033[0m      Run release\n"
	@printf "  \033[38;5;208m▶ rund\033[0m     Run debug\n"
	@printf "  \033[38;5;208m▶ gdb\033[0m      Debug in gdb\n"
	@printf "  \033[38;5;208m▶ val\033[0m      Debug in valgrind\n\n"
	@printf "  \033[38;5;208m▶ pick\033[0m     Pick & build game\n"
	@printf "  \033[38;5;208m▶ runp\033[0m     Pick & run game\n\n"
	@printf "  \033[38;5;208m▶ package\033[0m  Package game (auto)\n"
	@printf "  \033[38;5;208m▶ clean\033[0m    Clean build & dist\n"
	@printf "  \033[38;5;208m▶ flecs\033[0m    Rebuild Flecs ECS\n\n"

.DEFAULT_GOAL := help

# catching memory errors >
# 	CFLAGS_DEV += -fsanitize=address,undefined
# catching leaks >
# 	CFLAGS_DEV += -fsanitize=address,leak -fno-omit-frame-pointer