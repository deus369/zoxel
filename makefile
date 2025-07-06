# ==== zoxel minimal Makefile (main.c only) ====

# gcc -std=gnu99 -D_DEFAULT_SOURCE -fPIC -Wno-stringop-overread -Wno-stringop-overflow -Ofast -D NDEBUG -s -flto  -o build/zoxel-linux/zoxel src/main.c -Llib -Iinclude -Wl,-rpath='lib'  -lm -lpthread -lflecs  -Dzox_lib_sdl -lSDL2 -Dzox_lib_sdl_images -lSDL2_image -Dzox_lib_sdl_mixer -lSDL2_mixer -lGL

CC      := gcc
CFLAGS  := -fPIC -O3
# -std=gnu99 -D_DEFAULT_SOURCE -DNDEBUG
# -Wno-stringop-overread -Wno-stringop-overflow

CFLAGS_DEV := -fPIC -Wall -O0 -ggdb3 -g
# catching memory errors >
# CFLAGS_DEV += -fsanitize=address,undefined
# catching leaks >
# CFLAGS_DEV += -fsanitize=address,leak -fno-omit-frame-pointer
             # -Wno-stringop-overread -Wno-stringop-overflow

INCLUDES:= -Iinclude
LDFLAGS := -lm -lpthread -lflecs -lSDL2 -lSDL2_image -lSDL2_mixer -lGL
LDFLAGS += -Dzox_lib_sdl -Dzox_lib_sdl_mixer -Dzox_lib_sdl_images # in game defines

GAME    := zoxel
SRCS    := src/main.c
TARGET  := build/$(GAME)-linux/$(GAME)
TARGET_DEV := build/$(GAME)-linux/$(GAME)-debug

.PHONY: all clean run dev run-dev

# Release build\all: $(TARGET)
$(TARGET): $(SRCS) | build
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $@ $(LDFLAGS)

# Development build with debug symbols
dev: $(TARGET_DEV)

$(TARGET_DEV): $(SRCS) | build
	$(CC) $(CFLAGS_DEV) $(INCLUDES) $(SRCS) -o $@ $(LDFLAGS)

# Create build directory
build:
	mkdir -p build

# Remove build artifacts
clean:
	rm -rf build

# Run release build
run: all
	./$(TARGET)

# Run debug build
run-dev: dev
	./$(TARGET_DEV)

# Run debug build
run-gdb: dev
	gdb ./$(TARGET_DEV)

# Run debug build
run-valgrind: dev
	valgrind ./$(TARGET_DEV)
