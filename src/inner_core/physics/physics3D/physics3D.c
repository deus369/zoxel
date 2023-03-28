#ifndef zoxel_physics3D
#define zoxel_physics3D

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

zoxel_begin_module(Physics3D)
zoxel_define_component(Velocity3D)
zoxel_define_component(Acceleration3D)
zoxel_define_component(Torque3D)
zoxel_define_component(Bounds3D)
zoxel_define_component(Gravity3D)
zoxel_system(world, Friction3DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity3D, [out] Acceleration3D)
zoxel_system(world, Gravity3DSystem, EcsOnUpdate, [in] Gravity3D, [out] Acceleration3D)
zoxel_system(world, Acceleration3DSystem, EcsOnUpdate, [in] Acceleration3D, [out] Velocity3D)
zoxel_system(world, Velocity3DSystem, EcsOnUpdate, [out] Position3D, [in] Velocity3D)
zoxel_system(world, Bounds3DSystem, EcsOnUpdate, [in] Bounds3D, [out] Position3D)
zoxel_system(world, Acceleration3DResetSystem, EcsPostUpdate, [out] Acceleration3D)
// ECS_SYSTEM_DEFINE(world, Torque2DSystem, EcsOnUpdate, [out] Rotation2D, [in] Torque2D);
// ECS_SYSTEM_DEFINE(world, Friction2DSystem, EcsOnUpdate, [none] physics.Frictioned, [out] Velocity2D);
zoxel_end_module(Physics3D)

#endif