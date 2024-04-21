#ifndef zoxel_core
#define zoxel_core

// zoxel_settings
unsigned char cpu_tier;
#include "platforms/util/platform_defines.c"
#include "util/logs.c"
#include "ecs/ecs.c"
#include "maths/maths.c"
#include "platforms/platforms.c"
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "terminals/terminals.c"
#include "inputs/inputs.c"
#include "apps/apps.c"          // test removing sdl for engine stability
#include "files/files.c"        // uses sdl path function atm
#include "cameras/cameras.c"
#include "rendering/rendering.c"
#include "sounds/sounds.c"
#include "games/games.c"
#include "util/core_util.c"

unsigned char initialize_core(ecs_world_t *world) {
    if (initialize_pathing() == EXIT_FAILURE) return EXIT_FAILURE;
    if (initialize_apps(world) == EXIT_FAILURE) return EXIT_FAILURE;
    if (initialize_rendering(world) == EXIT_FAILURE) return EXIT_FAILURE;
    initialize_sounds(world);
    initialize_games(world);
    return EXIT_SUCCESS;
}

void dispose_core(ecs_world_t *world) {
    dispose_ecs(world);
    dispose_games(world);
    dispose_generic(world);
    dispose_apps(world);
    dispose_sounds(world);
    dispose_rendering(world);
    if (!headless) {
        close_sdl_input();
        close_sdl_video();
        close_audio_sdl();
    }
}

void spawn_prefabs_core(ecs_world_t *world) {
    spawn_prefabs_platforms(world);
    spawn_prefabs_generic(world);
    spawn_prefabs_files(world);
    spawn_prefabs_terminals(world);
#ifndef zox_disable_module_networking
    spawn_prefabs_networking(world);
#endif
    spawn_prefabs_inputs(world);
    if (!headless) spawn_prefabs_apps(world); // sdl
    spawn_prefabs_rendering(world);
    spawn_prefabs_sounds(world);
    spawn_prefabs_cameras(world);
    spawn_prefabs_games(world);
}

zox_begin_module(Core)
zox_import_module(Platforms)
zox_import_module(Generic)
zox_import_module(Maths)
zox_import_module(Timing)
zox_import_module(Transforms)
zox_import_module(Files)
zox_import_module(Terminals)
#ifndef zox_disable_module_networking
zox_import_module(Networking)
#endif
zox_import_module(Inputs)
if (!headless) zox_import_module(Apps) // sdl
zox_import_module(Rendering)
zox_import_module(Sounds)
zox_import_module(Cameras)
zox_import_module(Games)
zoxel_end_module(Core)

#endif
