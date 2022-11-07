#ifndef zoxel_physics
#define zoxel_physics

// tags
ECS_DECLARE(Frictioned);
// components
zoxel_component(DisableMovement, bool);
// sub modules
#include "physics2D/physics2D.c"
#include "physics3D/physics3D.c"

void PhysicsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics);
    ECS_TAG_DEFINE(world, Frictioned);
    ECS_COMPONENT_DEFINE(world, DisableMovement);
    ECS_IMPORT(world, Physics2D);
    ECS_IMPORT(world, Physics3D);
}
#endif