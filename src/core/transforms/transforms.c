#ifndef Zoxel_Transforms
#define Zoxel_Transforms

// Sub Modules
#include "transforms2D/transforms2D.c"
#include "transforms3D/transforms3D.c"

//! core transforms grabs dimension based sub modules.
void TransformsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Transforms);
    ECS_IMPORT(world, Transforms2D);
    ECS_IMPORT(world, Transforms3D);
}
#endif