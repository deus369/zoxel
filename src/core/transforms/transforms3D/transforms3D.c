#ifndef zoxel_transforms3D
#define zoxel_transforms3D

// EcsPostUpdate | EcsPreStore
#define zox_transforms_stage EcsPreStore
// zoxel_component_includes
zox_declare_tag(EulerOverride)
zox_component(Position3D, float3)
zox_component(LastPosition3D, float3)
zox_component(Rotation3D, float4)     //! A quaternion rotation
zox_component(Scale, float3)          //! A Non Uniform 3D Scale
zox_component(UniformScale, float)    //! A Uniform scale used generically
zox_component(Matrix, float4x4)       //! A matrix used for rendering
zox_component(Euler, float3)          //! A rotation but kept in euler form
zox_component(EulerLimitX, float2)    //! a limitation of euler x axis
zox_component(EulerLimitZ, float2)    //! a limitation of euler z axis
zox_component(LocalPosition3D, float3)
zox_component(LocalRotation3D, float4)
// zoxel_util_includes
#include "util/transform3d_util.c"
// zoxel_system_includes
#include "systems/euler_limit_z_system.c"
#include "systems/euler_override_system.c"
#include "systems/parent_position_system.c"
#include "systems/parent_rotation_system.c"

zox_begin_module(Transforms3D)
// zoxel_component_defines
zox_define_tag(EulerOverride)
zox_define_component(Position3D)
zox_define_component(LastPosition3D)
zox_define_component(Rotation3D)
zox_define_component(Scale)
zox_define_component(UniformScale)
zox_define_component(Matrix)
zox_define_component(Euler)
zox_define_component(EulerLimitX)
zox_define_component(EulerLimitZ)
zox_define_component(LocalPosition3D)
zox_define_component(LocalRotation3D)
// zoxel_system_defines
zox_system(EulerLimitXSystem, EcsOnUpdate, [in] EulerLimitX, [out] Euler)
zox_system(EulerLimitZSystem, EcsOnUpdate, [in] EulerLimitZ, [out] Euler)
zox_system(EulerOverrideSystem, EcsOnUpdate, [none] EulerOverride, [in] Euler, [out] Rotation3D)
zox_system(ParentRotationSystem, zox_transforms_stage, [in] ParentLink, [in] LocalRotation3D, [out] Rotation3D)
zox_system(ParentPositionSystem, zox_transforms_stage, [in] ParentLink, [in] LocalPosition3D, [out] Position3D)
zoxel_end_module(Transforms3D)

// todo: remove euler use, and find a way to limit quaternion rotations used for camera atm
//      ai mentioned something about using axis and angle of a quaternion

#endif