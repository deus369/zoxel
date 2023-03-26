#ifndef zoxel_core
#define zoxel_core

unsigned char profiler = 0;
ecs_world_t *world;
#include "util/logs.c"
#include "util/ecs/ecs.c"
#include "maths/maths.c"
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "apps/apps.c"
#include "inputs/inputs.c"
#include "cameras/cameras.c"
#include "rendering/rendering.c"
#include "sounds/sounds.c"
#include "util/core_util.c"

zoxel_begin_module(Core)
zoxel_import_module(Generic)
zoxel_import_module(Maths)
zoxel_import_module(Timing)
zoxel_import_module(Transforms)
zoxel_import_module(Networking)
if (!headless) zoxel_import_module(Apps)
if (!headless) zoxel_import_module(Inputs)
zoxel_import_module(Rendering)
zoxel_import_module(Sounds)
zoxel_import_module(Cameras)
zoxel_end_module(Core)
#endif