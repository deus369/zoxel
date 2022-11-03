#ifndef Zoxel_Physics3D
#define Zoxel_Physics3D

// Components
//! Velocity movement of a 3D Entity.
zoxel_component(Velocity, float3);
//! How fast Velocity moves over time.
zoxel_component(Acceleration, float3);
//! How fast Rotation moves over time.
zoxel_component(Torque, float4);
// Systems
#include "Systems/Velocity3DSystem.c"
#include "Systems/Acceleration3DSystem.c"
//#include "Systems/TorqueSystem.c"
//#include "Systems/FrictionSystem.c"

void Physics3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics3D);
    ECS_COMPONENT_DEFINE(world, Velocity);
    ECS_COMPONENT_DEFINE(world, Acceleration);
    ECS_COMPONENT_DEFINE(world, Torque);
    ECS_SYSTEM_DEFINE(world, Velocity3DSystem, EcsOnUpdate, [out] Position, [in] Velocity);
    ECS_SYSTEM_DEFINE(world, Acceleration3DSystem, EcsOnUpdate, [out] Velocity, [out] Acceleration);
    // ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
    // ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [out] Velocity2D);
}
#endif