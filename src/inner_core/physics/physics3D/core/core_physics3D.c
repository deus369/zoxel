#ifndef zoxel_core_physics3D
#define zoxel_core_physics3D

#define physics3D_gravity -1.97f
zoxel_component(Velocity3D, float3)     //! Velocity movement of a 3D Entity.
zoxel_component(Acceleration3D, float3) //! How fast Velocity moves over time.
zoxel_component(Torque3D, float4)       //! How fast Rotation3D moves over time.
zoxel_component(Bounds3D, float3)       //! Velocity movement of a 3D Entity.
zoxel_component(Gravity3D, float3)      //! A constant acceleration towards something
#include "util/physics3D_util.c"
#include "systems/velocity3D_system.c"
#include "systems/acceleration3D_system.c"
#include "systems/acceleration3D_reset_system.c"
#include "systems/friction3D_system.c"
#include "systems/bounds3D_system.c"
#include "systems/gravity3D_system.c"

zoxel_begin_module(CorePhysics3D)
zoxel_define_component(Velocity3D)
zoxel_define_component(Acceleration3D)
zoxel_define_component(Torque3D)
zoxel_define_component(Bounds3D)
zoxel_define_component(Gravity3D)
zoxel_system(Velocity3DSystem, EcsOnUpdate, [out] Position3D, [in] Velocity3D)
zoxel_system(Bounds3DSystem, EcsOnUpdate, [in] Bounds3D, [out] Position3D)
zoxel_system(Gravity3DSystem, EcsOnUpdate, [in] Gravity3D, [out] Acceleration3D)
zoxel_system(Friction3DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity3D, [out] Acceleration3D)
zoxel_system(Acceleration3DSystem, EcsOnUpdate, [in] Acceleration3D, [out] Velocity3D)
zoxel_system(Acceleration3DResetSystem, EcsPostUpdate, [out] Acceleration3D)
// ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
// ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [out] Velocity2D);
zoxel_end_module(CorePhysics3D)

#endif