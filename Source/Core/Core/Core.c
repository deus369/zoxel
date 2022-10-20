#ifndef Zoxel_Core
#define Zoxel_Core

// Data
#include "Data/float2.c"
#include "Data/float3.c"
#include "Data/float4.c"
#include "Data/float4x4.c"
#include "Data/double2.c"
#include "Data/int2.c"
#include "Data/color.c"
// Util
#include "Util/math.c"
#include "Util/flecs_extensions.c"
// Components
#include "Components/EntityDirty.c"
#include "Components/ID.c"
#include "Components/Seed.c"
// Systems
#include "Systems/EntityDirtyResetSystem.c"

void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_COMPONENT_DEFINE(world, EntityDirty);
    ECS_COMPONENT_DEFINE(world, ID);
    ECS_COMPONENT_DEFINE(world, Seed);
    // https://flecs.docsforge.com/master/manual/#staging
    // These are phases, you can create custom phases
    // EcsOnLoad, EcsPostLoad, EcsPreUpdate, EcsOnUpdate, EcsOnValidate, EcsPostUpdate, EcsPreStore, EcsOnStore
    // System ran in the EcsOnValidate phase
    // ECS_SYSTEM(world, DetectCollisions, EcsOnValidate, Position);
    // Generic EntityDirty System - turns EntityDirty Value back to 0 after one frame.
    //! \todo Add ZOXEL_SYSTEM_MULTITHREADED after
    ECS_SYSTEM_DEFINE(world, EntityDirtyResetSystem, EcsPostUpdate, [out] EntityDirty);
}

#endif