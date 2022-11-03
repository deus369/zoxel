#ifndef Zoxel_Physics2D
#define Zoxel_Physics2D

// Components
//! Velocity movement of a 2D Entity.
zoxel_component(Velocity2D, float2);
//! Velocity movement of a 2D Entity.
zoxel_component(Acceleration2D, float2);
//! Velocity movement of a 2D Entity.
zoxel_component(Torque2D, float);
// Util
#include "Util/Physics2DUtil.c"
// Systems
#include "Systems/Friction2DSystem.c"
#include "Systems/Acceleration2DSystem.c"
#include "Systems/Velocity2DSystem.c"
#include "Systems/Torque2DSystem.c"

void Physics2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics2D);
    ECS_COMPONENT_DEFINE(world, Velocity2D);
    ECS_COMPONENT_DEFINE(world, Torque2D);
    ECS_COMPONENT_DEFINE(world, Acceleration2D);
    zoxel_system(world, Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity2D, [out] Acceleration2D);
    zoxel_system(world, Acceleration2DSystem, EcsOnUpdate, [out] Velocity2D, [out] Acceleration2D);
    zoxel_system(world, Velocity2DSystem, EcsOnUpdate, [out] Position2D, [in] Velocity2D);
    zoxel_system(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
}
#endif