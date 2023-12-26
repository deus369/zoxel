#ifndef zox_engine
#define zox_engine

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
#ifndef zox_disable_audio
    #define SDL_MIXER
#endif
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

void dispose_zox(ecs_world_t *world) {
    dispose_inner_core(world);
    dispose_game_store();
    dispose_core(world);
}

unsigned char initialize_zox(ecs_world_t *world) {
    if (initialize_core(world) == EXIT_FAILURE) return EXIT_FAILURE;
    initialize_inner_core(world);
    initialize_outer_core(world);
    return EXIT_SUCCESS;
}

void spawn_prefabs_engine(ecs_world_t *world) {
    spawn_prefabs_core(world);
    spawn_prefabs_inner_core(world);
    spawn_prefabs_outer_core(world);
    spawn_prefabs_users(world);
    spawn_prefabs_gameplay(world);
    spawn_prefabs_space(world);
}

zox_begin_module(Zox)
zox_import_module(Core)
zox_import_module(InnerCore)
zox_import_module(OuterCore)
zox_import_module(Users)
zox_import_module(Gameplay)
zox_import_module(Space)
zoxel_end_module(Zox)

#endif
