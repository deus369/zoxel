#ifndef zoxel_outer_core
#define zoxel_outer_core

#include "cubes/cubes.c"
#include "ai/ai.c"
#include "particles/particles.c"

void OuterCoreImport(ecs_world_t *world)
{
    zoxel_module(OuterCore)
    zoxel_import_module(Cubes)
    zoxel_import_module(AI)
    zoxel_import_module(Particles)
}
#endif