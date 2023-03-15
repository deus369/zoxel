#ifndef zoxel_core
#define zoxel_core

// Settings for main
unsigned char profiler = 0;
// util
#include "util/logs.c"
#include "util/ecs/ecs.c"
// modules
#include "maths/maths.c"
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "apps/apps.c"
#include "inputs/inputs.c"
#include "cameras/cameras.c"
#include "rendering/rendering.c"
// core loop
#include "util/core_util.c"

//! Handles modules that are for basic stuff at lowest level
void CoreImport(ecs_world_t *world) {
    zoxel_module(Core)
    zoxel_import_module(Generic)
    zoxel_import_module(Maths)
    zoxel_import_module(Timing)
    zoxel_import_module(Transforms)
    zoxel_import_module(Networking)
    if (!headless) {
        zoxel_import_module(Apps)
        zoxel_import_module(Inputs)
    }
    zoxel_import_module(Rendering)
    zoxel_import_module(Cameras)
    zoxel_log("     > imported core\n");
}
#endif