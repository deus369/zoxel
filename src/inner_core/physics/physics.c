#ifndef zoxel_physics
#define zoxel_physics

zoxel_declare_tag(Frictioned)
zoxel_state_component(DisableMovement)
#include "physics2D/physics2D.c"
#include "physics3D/physics3D.c"

void PhysicsImport(ecs_world_t *world)
{
    zoxel_module(Physics)
    zoxel_define_tag( Frictioned)
    zoxel_define_component(DisableMovement)
    zoxel_import_module(Physics2D)
    zoxel_import_module(Physics3D)
}
#endif