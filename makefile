# ==== Zoxel ====

GAME    	:= zoxel
SRC_DIR 	:= src
SRC    		:= src/main.c
SRCS 		:= $(shell find $(SRC_DIR) -name "*.c")  # Recursive
TARGET  	:= build/$(GAME)
TARGET_DEV 	:= build/$(GAME)-debug
CC      	:= gcc
CFLAGS  	:= -O3 -fPIC
CFLAGS_DEV 	:= -O0 -fPIC -g -Wall -ggdb3 # -Wshadow -Wpedantic -fno-omit-frame-pointer
LDFLAGS 	:= -lm -lpthread -lflecs -lSDL2 -lSDL2_image -lSDL2_mixer -lGL
LDFLAGS 	+= -Dzox_lib_sdl -Dzox_lib_sdl_mixer -Dzox_lib_sdl_images

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

dev: $(TARGET_DEV)

$(TARGET_DEV): $(SRCS)
	$(CC) $(CFLAGS_DEV) $(INCLUDES) $(SRC) -o $@ $(LDFLAGS)

run-dev: dev
	./$(TARGET_DEV)

gdb: dev
	gdb ./$(TARGET_DEV)

valgrind: dev
	valgrind ./$(TARGET_DEV)

clean:
	rm -rf build

flecs:
	cd ../flecsing && make clean && make download && make refresh

.PHONY: all run dev run-dev run-gdb run-val clean

# catching memory errors >
# 	CFLAGS_DEV += -fsanitize=address,undefined
# catching leaks >
# 	CFLAGS_DEV += -fsanitize=address,leak -fno-omit-frame-pointer