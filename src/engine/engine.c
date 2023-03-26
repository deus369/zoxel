#ifndef zoxel_engine
#define zoxel_engine

#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
#include "../../include/flecs.h"
#define SDL_IMAGES
#define SDL_MIXER
// #define USE_SDL_3
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror
unsigned char server_mode = 0;
#include "util/platforms_util.c"
#include "../core/core.c"
#include "../inner_core/inner_core.c"
#include "../outer_core/outer_core.c"
#include "../gameplay/gameplay.c"
#include "../space/space.c"
#include "util/engine_util.c"

zoxel_begin_module(ZoxelEngine)
zoxel_import_module(Core)
zoxel_import_module(InnerCore)
zoxel_import_module(OuterCore)
zoxel_import_module(Gameplay)
zoxel_import_module(Space)
zoxel_end_module(ZoxelEngine)

// todo: move some things to sdl module in core
#endif