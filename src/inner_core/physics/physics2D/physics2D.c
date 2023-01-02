#ifndef zoxel_physics2D
#define zoxel_physics2D

// components
//! Velocity movement of a 2D Entity.
zoxel_component(Velocity2D, float2);
//! Velocity movement of a 2D Entity.
zoxel_component(Acceleration2D, float2);
//! Velocity movement of a 2D Entity.
zoxel_component(Torque2D, float);
//! Velocity movement of a 2D Entity.
zoxel_component(Bounds2D, float2);
// util
#include "util/physics2D_util.c"
// systems
#include "systems/friction2D_system.c"
#include "systems/acceleration2D_system.c"
#include "systems/velocity2D_system.c"
#include "systems/torque2D_system.c"
#include "systems/bounds2D_system.c"
#include "systems/gravity2D_system.c"

void Physics2DImport(ecs_world_t *world)
{
    zoxel_module(Physics2D)
    ECS_COMPONENT_DEFINE(world, Velocity2D);
    ECS_COMPONENT_DEFINE(world, Torque2D);
    ECS_COMPONENT_DEFINE(world, Acceleration2D);
    ECS_COMPONENT_DEFINE(world, Bounds2D);
    zoxel_system(world, Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity2D, [out] Acceleration2D);
    zoxel_system(world, Acceleration2DSystem, EcsOnUpdate, [out] Velocity2D, [out] Acceleration2D);
    zoxel_system(world, Velocity2DSystem, EcsOnUpdate, [out] Position2D, [in] Velocity2D);
    zoxel_system(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
    zoxel_system(world, Bounds2DSystem, EcsOnUpdate, [out] Position2D, [in] Bounds2D);
}
#endif