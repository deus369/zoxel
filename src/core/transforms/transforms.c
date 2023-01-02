#ifndef zoxel_transforms
#define zoxel_transforms

// shared components
//! Scales an entities transform in 1D.
zoxel_component(Scale1D, float);
// Sub Modules
#include "hierarchy/hierarchy.c"
#include "transforms2D/transforms2D.c"
#include "transforms3D/transforms3D.c"

//! core transforms grabs dimension based sub modules.
/**
*   \todo Check out on_delete hooks for children deletions.
*/
void TransformsImport(ecs_world_t *world)
{
    zoxel_module(Transforms)
    ECS_COMPONENT_DEFINE(world, Scale1D);
    ECS_IMPORT(world, Hierarchys);
    ECS_IMPORT(world, Transforms2D);
    ECS_IMPORT(world, Transforms3D);
}
#endif