#ifndef Zoxel_Transforms
#define Zoxel_Transforms

// Sub Modules
#include "Transforms2D/Transforms2D.c"
#include "Transforms3D/Transforms3D.c"

//! Core Transforms grabs dimension based sub modules.
void TransformsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Transforms);
    ECS_IMPORT(world, Transforms2D);
    ECS_IMPORT(world, Transforms3D);
}
#endif