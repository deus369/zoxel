#ifndef zoxel_core_physics3D
#define zoxel_core_physics3D

#define physics3D_gravity -3.97f // -1.97f
const float friction3D = 6.0f;  // 0.002
zox_component(Velocity3D, float3)     //! Velocity movement of a 3D Entity.
zox_component(Acceleration3D, float3) //! How fast Velocity moves over time.
// zox_component(Torque3D, float4)
zox_component(Omega3D, float4)
zox_component(Alpha3D, float4)
zox_component(Gravity3D, float3)      //! A constant acceleration towards something
zox_byte_component(InitializePhysics3D)
#include "util/physics3D_util.c"
#include "systems/velocity3D_system.c"
#include "systems/acceleration3D_system.c"
#include "systems/omega3D_system.c"
#include "systems/alpha3D_system.c"
#include "systems/friction3D_system.c"
#include "systems/dissipation3D_system.c"
#include "systems/bounds3D_system.c"
#include "systems/gravity3D_system.c"
#include "systems/physics3D_disable_system.c"
#include "systems/bounds3D_grow_system.c"

zox_begin_module(CorePhysics3D)
zox_define_component(Velocity3D)
zox_define_component(Acceleration3D)
zox_define_component(Omega3D)
zox_define_component(Alpha3D)
zox_define_component(Gravity3D)
zox_define_component(InitializePhysics3D)
zox_system(Velocity3DSystem, EcsOnUpdate, [out] Position3D, [in] Velocity3D)
zox_system(Omega3DSystem, EcsOnUpdate, [in] Omega3D, [out] Rotation3D)
zox_system(Physics3DDisableSystem, EcsOnUpdate, [out] InitializePhysics3D, [out] Position3D, [out] Velocity3D)
// zox_system(Bounds3DSystem, EcsOnUpdate, [in] Bounds3D, [out] Position3D)
zox_system(Bounds3DGrowSystem, EcsPreStore, [in] MeshDirty, [in] ChunkSize, [in] Bounds3D)
zox_system(Gravity3DSystem, EcsOnUpdate, [in] Gravity3D, [out] Acceleration3D)
zox_system(Friction3DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Velocity3D, [out] Acceleration3D)
zox_system(Dissipation3DSystem, EcsOnUpdate, [none] physics.Frictioned, [in] Omega3D, [out] Alpha3D)
zox_system(Acceleration3DSystem, EcsOnUpdate, [out] Acceleration3D, [out] Velocity3D)
zox_system(Alpha3DSystem, EcsOnUpdate, [out] Alpha3D, [out] Omega3D)
zoxel_end_module(CorePhysics3D)

#endif