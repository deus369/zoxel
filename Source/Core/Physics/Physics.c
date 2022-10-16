#ifndef Zoxel_Physics
#define Zoxel_Physics

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

// Components
#include "Components/Velocity.c"
#include "Components/Torque.c"
#include "Components/Acceleration.c"
// Tags
/*ECS_DECLARE(Frictioned);
// Systems
#include "Systems/VelocitySystem.c"
#include "Systems/AccelerationSystem.c"
#include "Systems/TorqueSystem.c"
#include "Systems/FrictionSystem.c"*/

void PhysicsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Physics);
    ECS_COMPONENT_DEFINE(world, Velocity);
    ECS_COMPONENT_DEFINE(world, Torque);
    ECS_COMPONENT_DEFINE(world, Acceleration);
    /*ECS_TAG_DEFINE(world, Frictioned);
    ECS_SYSTEM_DEFINE(world, Velocity2DSystem, EcsOnUpdate, [out] Position2D, [in] Velocity2D);
    ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
    ECS_SYSTEM_DEFINE(world, Acceleration2DSystem, EcsOnUpdate, [out] Velocity2D, [out] Acceleration2D);
    ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, [none] Frictioned, [out] Velocity2D);*/
}
#endif