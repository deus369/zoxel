#ifndef zoxel_physics3D
#define zoxel_physics3D

// components
//! Velocity movement of a 3D Entity.
zoxel_component(Velocity3D, float3);
//! How fast Velocity moves over time.
zoxel_component(Acceleration3D, float3);
//! How fast Rotation moves over time.
zoxel_component(Torque3D, float4);
//! Velocity movement of a 3D Entity.
zoxel_component(Bounds3D, float3);
// util
#include "util/physics3D_util.c"
// systems
#include "systems/velocity3D_system.c"
#include "systems/acceleration3D_system.c"
#include "systems/friction3D_system.c"
#include "systems/bounds3D_system.c"
//#include "systems/TorqueSystem.c"

void Physics3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics3D);
    ECS_COMPONENT_DEFINE(world, Velocity3D);
    ECS_COMPONENT_DEFINE(world, Acceleration3D);
    ECS_COMPONENT_DEFINE(world, Torque3D);
    ECS_COMPONENT_DEFINE(world, Bounds3D);
    zoxel_system(world, Friction3DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity3D, [out] Acceleration3D);
    zoxel_system(world, Acceleration3DSystem, EcsOnUpdate, [out] Velocity3D, [out] Acceleration3D);
    zoxel_system(world, Velocity3DSystem, EcsOnUpdate, [out] Position, [in] Velocity3D);
    zoxel_system(world, Bounds3DSystem, EcsOnUpdate, [out] Position, [in] Bounds3D);
    // ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
    // ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [out] Velocity2D);
}
#endif