# Request POSIX Make behavior and disable any default suffix-based rules
# .POSIX:
# .SUFFIXES:

# Declare compiler tools and flags
CC      = cc
#CC      = gcc
CFLAGS  = -std=c99
CFLAGS += -fPIC -g
#-Og
# CFLAGS += -Wall -Wextra -Wpedantic
# CFLAGS += -Wno-unused-parameter -Wno-unused-result -Wno-unused-function
# CFLAGS += -Isrc/
LDFLAGS =
LDLIBS  = -lGL -lSDL2
LDLIBS  += -D NDEBUG -O3 -flto
# flecs
SRCS = src/flecs/flecs.c src/flecs/flecs.h
OBJS = src/flecs/flecs.c
# main
SRCS += src/main.c
OBJS += src/main.c

# Build the main executable 
zoxel.x86: $(SRCS) # src/main.c src/OpenGL/*.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Helper target that cleans up build artifacts
.PHONY: clean
clean:
	rm -fr zoxel zoxel.exe src/*.o

# Default rule for compiling .c files to .o object files
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


#SRCS=$(wildcard src/*.h src/*.c)
#SRC2=$(wildcard src/*.c)

# OBJS=src/main.o src/OpenGL/OpenGLHelpers.o src/OpenGL/opengl.o
# OBJS=$(wildcard src/*.o) # src/main.o src/OpenGL/opengl.o src/OpenGL/OpenGLHelpers.o
# $(wildcard src/*.o) # 
# OBJ=$(SRC2:.c=.o)
   
# $(CC) $(CFLAGS) -c -o $(SRCS) $(OBJS)


#main.o: main.c
#	$(CC) $(CFLAGS) $(LDFLAGS) -c -o main.c

# $(CC) $(CFLAGS) $(LDFLAGS) -o $(OBJS) $(LDLIBS)
# src/OpenGL/*.c src/OpenGL/*.h src/OpenGL/*.c 

# rm src/*.o