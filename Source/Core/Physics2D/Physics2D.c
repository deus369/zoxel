#ifndef Zoxel_Physics2D
#define Zoxel_Physics2D

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

// Tags
ECS_DECLARE(Frictioned);
// Components
#include "Components/Velocity2D.c"
#include "Components/Torque2D.c"
#include "Components/Acceleration2D.c"
// Systems
#include "Systems/Friction2DSystem.c"
#include "Systems/Acceleration2DSystem.c"
#include "Systems/Velocity2DSystem.c"
#include "Systems/Torque2DSystem.c"

void Physics2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics2D);
    ECS_TAG_DEFINE(world, Frictioned);
    ECS_COMPONENT_DEFINE(world, Velocity2D);
    ECS_COMPONENT_DEFINE(world, Torque2D);
    ECS_COMPONENT_DEFINE(world, Acceleration2D);
    ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, [none] Frictioned, [in] Velocity2D, [out] Acceleration2D);
    ECS_SYSTEM_DEFINE(world, Acceleration2DSystem, EcsOnUpdate, [out] Velocity2D, [out] Acceleration2D);
    ECS_SYSTEM_DEFINE(world, Velocity2DSystem, EcsOnUpdate, [out] Position2D, [in] Velocity2D);
    ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
    ecs_system_enable_multithreading(world, ecs_id(Friction2DSystem));
    ecs_system_enable_multithreading(world, ecs_id(Acceleration2DSystem));
    ecs_system_enable_multithreading(world, ecs_id(Velocity2DSystem));
    ecs_system_enable_multithreading(world, ecs_id(Torque2DSystem));
}

/*ecs_system(world, {
    .entity = ecs_id(Velocity2DSystem),
    .multi_threaded = true
});*/
#endif