// include file for core
#ifndef Zoxel_Physics2D
#define Zoxel_Physics2D

#include "Components/Velocity2D.c"
#include "Components/Torque2D.c"
#include "Systems/Torque2DSystem.c"
#include "Systems/Velocity2DSystem.c"

void InitializePhysics2D(ecs_world_t *world)
{
    ECS_COMPONENT(world, Velocity2D);
    ECS_COMPONENT(world, Torque2D);
    ECS_SYSTEM(world, Velocity2DSystem, EcsOnUpdate, Position2D, Velocity2D);
    ECS_SYSTEM(world, Torque2DSystem, EcsOnUpdate, Rotation2D, Torque2D);
    // ECS_SYSTEM(world, Gravity2DSystem, EcsOnUpdate, Position2D, Torque2D);
}

#endif