#ifndef zoxel_engine
#define zoxel_engine

// todo: move some things to sdl module in core
// todo: position confusing, move to above directory for easier to understand navigation
// engine imports, besides sub modules, it's core is flecs
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
#include "../../include/flecs.h"
#define SDL_MIXER
#include "util/events.c"
#include "../core/core.c"
#include "util/game_store_util.c"
#include "../inner_core/inner_core.c"
#include "../outer_core/outer_core.c"
#include "../users/users.c"
#include "../gameplay/gameplay.c"
#include "../space/space.c"
#include "util/engine_util.c"
#include "util/main_loop_util.c"

void load_resources_engine(ecs_world_t *world) {
    load_resources_inner_core(world);
    load_resources_outer_core(world);
}

void spawn_prefabs_engine(ecs_world_t *world) {
    spawn_prefabs_core(world);
    spawn_prefabs_inner_core(world);
    spawn_prefabs_outer_core(world);
    spawn_prefabs_users(world);
    spawn_prefabs_gameplay(world);
    spawn_prefabs_space(world);
}

zox_begin_module(ZoxelEngine)
zox_import_module(Core)
zox_import_module(InnerCore)
zox_import_module(OuterCore)
zox_import_module(Users)
zox_import_module(Gameplay)
zox_import_module(Space)
zoxel_end_module(ZoxelEngine)

#endif

// #define USE_SDL_3
