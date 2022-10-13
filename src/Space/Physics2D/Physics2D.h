#ifndef Zoxel_Physics2D
#define Zoxel_Physics2D

// Components
#include "Components/Velocity2D.c"
#include "Components/Torque2D.c"
#include "Components/Acceleration2D.c"
// Tags
ECS_DECLARE(Frictioned);
// Systems
#include "Systems/Velocity2DSystem.c"
#include "Systems/Acceleration2DSystem.c"
#include "Systems/Torque2DSystem.c"
#include "Systems/Friction2DSystem.c"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

void Physics2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics2D);
    ECS_COMPONENT_DEFINE(world, Velocity2D);
    ECS_COMPONENT_DEFINE(world, Torque2D);
    ECS_COMPONENT_DEFINE(world, Acceleration2D);
    ECS_TAG_DEFINE(world, Frictioned);
    ECS_SYSTEM_DEFINE(world, Velocity2DSystem, EcsOnUpdate, Position2D, Velocity2D);
    ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, Rotation2D, Torque2D);
    ECS_SYSTEM_DEFINE(world, Acceleration2DSystem, EcsOnUpdate, Velocity2D, Acceleration2D);
    ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, Frictioned, Velocity2D);
}
#endif