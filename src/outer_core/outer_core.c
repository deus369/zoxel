#ifndef zoxel_outer_core
#define zoxel_outer_core

// --- Outer core ---
#include "cubes/cubes.c"
#include "ai/ai.c"
#include "particles/particles.c"

void OuterCoreImport(ecs_world_t *world)
{
    zoxel_module(OuterCore)
    ECS_IMPORT(world, Cubes);
    ECS_IMPORT(world, AI);
    ECS_IMPORT(world, Particles);
}
#endif