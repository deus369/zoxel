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
#include "util/events.c"
#include "util/platforms_util.c"
#include "../core/core.c"
#include "../inner_core/inner_core.c"
#include "../outer_core/outer_core.c"
#include "../users/users.c"
#include "../gameplay/gameplay.c"
#include "../space/space.c"
#include "util/engine_util.c"

void load_resources_engine(ecs_world_t *world) {
    load_resources_inner_core(world);
}

void spawn_prefabs_engine(ecs_world_t *world) {
    // zoxel_log(" + spawning prefabs core\n");
    spawn_prefabs_core(world);
    // zoxel_log(" + spawning prefabs inner core\n");
    spawn_prefabs_inner_core(world);
    // zoxel_log(" + spawning prefabs outer core\n");
    spawn_prefabs_outer_core(world);
    // zoxel_log(" + spawning prefabs gameplay\n");
    spawn_prefabs_gameplay(world);
    // zoxel_log(" + spawning prefabs space\n");
    spawn_prefabs_space(world);
    zoxel_log(" + spawned all prefabs\n");
}

zox_begin_module(ZoxelEngine)
zox_import_module(Core)
zox_import_module(InnerCore)
zox_import_module(OuterCore)
zox_import_module(Users)
zox_import_module(Gameplay)
zox_import_module(Space)
zoxel_end_module(ZoxelEngine)

// todo: move some things to sdl module in core

#endif