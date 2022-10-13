#ifndef Zoxel_Physics2D
#define Zoxel_Physics2D

#include "Components/Velocity2D.c"
#include "Components/Torque2D.c"
#include "Components/Acceleration2D.c"
ECS_COMPONENT_DECLARE(Velocity2D);
ECS_COMPONENT_DECLARE(Torque2D);
ECS_COMPONENT_DECLARE(Acceleration2D);
ECS_DECLARE(Frictioned);

#include "Systems/Velocity2DSystem.c"
#include "Systems/Acceleration2DSystem.c"
#include "Systems/Torque2DSystem.c"
#include "Systems/Friction2DSystem.c"
ECS_SYSTEM_DECLARE(Velocity2DSystem);
ECS_SYSTEM_DECLARE(Acceleration2DSystem);
ECS_SYSTEM_DECLARE(Torque2DSystem);
ECS_SYSTEM_DECLARE(Friction2DSystem);

void Physics2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics2D);
    ECS_COMPONENT_DEFINE(world, Velocity2D);
    ECS_COMPONENT_DEFINE(world, Torque2D);
    ECS_COMPONENT_DEFINE(world, Acceleration2D);
    ECS_TAG_DEFINE(world, Frictioned);
    // Systems
    ECS_SYSTEM_DEFINE(world, Velocity2DSystem, EcsOnUpdate, Position2D, Velocity2D);
    ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, Rotation2D, Torque2D);
    ECS_SYSTEM_DEFINE(world, Acceleration2DSystem, EcsOnUpdate, Velocity2D, Acceleration2D);
    ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, Frictioned, Velocity2D);
}

#endif