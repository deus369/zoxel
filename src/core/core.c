#ifndef zoxel_core
#define zoxel_core

// zoxel_settings
unsigned char cpu_tier;
#include "util/logs.c"
#include "ecs/ecs.c"
#include "maths/maths.c"
#include "platforms/platforms.c"
#include "timing/timing.c"
#include "generic/generic.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "terminals/terminals.c"
#include "inputs/inputs.c"
#include "apps/apps.c"          // test removing sdl for engine stability
#include "files/files.c"        // uses sdl path function atm
#include "cameras/cameras.c"
#include "rendering/rendering.c"
#include "sounds/sounds.c"
#include "util/core_util.c"

void spawn_prefabs_core(ecs_world_t *world) {
    spawn_prefabs_platforms(world);
    spawn_prefabs_generic(world);
    spawn_prefabs_files(world);
    spawn_prefabs_terminals(world);
    spawn_prefabs_networking(world);
    spawn_prefabs_inputs(world);
    if (!headless) spawn_prefabs_apps(world); // sdl
    spawn_prefabs_rendering(world);
    spawn_prefabs_sounds(world);
    spawn_prefabs_cameras(world);
}

zox_begin_module(Core)
zox_import_module(Platforms)
zox_import_module(Generic)
zox_import_module(Maths)
zox_import_module(Timing)
zox_import_module(Transforms)
zox_import_module(Files)
zox_import_module(Terminals)
zox_import_module(Networking)
zox_import_module(Inputs)
if (!headless) zox_import_module(Apps) // sdl
zox_import_module(Rendering)
zox_import_module(Sounds)
zox_import_module(Cameras)
zoxel_end_module(Core)

#endif