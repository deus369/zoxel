#ifndef zoxel_transforms3D
#define zoxel_transforms3D

// zoxel_component_includes
zoxel_declare_tag(EulerOverride)
zoxel_component(Position3D, float3)     //! A 3D Position3D component
zoxel_component(Rotation3D, float4)     //! A quaternion rotation
zoxel_component(Scale, float3)          //! A Non Uniform 3D Scale
zoxel_component(UniformScale, float)    //! A Uniform scale used generically
zoxel_component(Matrix, float4x4)       //! A matrix used for rendering
zoxel_component(Euler, float3)          //! A rotation but kept in euler form
zoxel_component(EulerLimitX, float2)    //! a limitation of euler x axis
zoxel_component(EulerLimitZ, float2)    //! a limitation of euler z axis
zoxel_component(LocalPosition3D, float3)
zoxel_component(LocalRotation3D, float4)
// zoxel_util_includes
#include "util/transform3d_util.c"
// zoxel_system_includes
#include "systems/euler_limit_z_system.c"
#include "systems/euler_override_system.c"
#include "systems/parent_position_system.c"
#include "systems/parent_rotation_system.c"

zoxel_begin_module(Transforms3D)
// zoxel_component_defines
zoxel_define_tag(EulerOverride)
zoxel_define_component(Position3D)
zoxel_define_component(Rotation3D)
zoxel_define_component(Scale)
zoxel_define_component(UniformScale)
zoxel_define_component(Matrix)
zoxel_define_component(Euler)
zoxel_define_component(EulerLimitX)
zoxel_define_component(EulerLimitZ)
zoxel_define_component(LocalPosition3D)
zoxel_define_component(LocalRotation3D)
// zoxel_system_defines
zox_system(EulerLimitXSystem, EcsOnUpdate, [in] EulerLimitX, [out] Euler)
zox_system(EulerLimitZSystem, EcsOnUpdate, [in] EulerLimitZ, [out] Euler)
zox_system(EulerOverrideSystem, EcsOnUpdate, [none] EulerOverride, [in] Euler, [out] Rotation3D)
zox_system(ParentRotationSystem, EcsPostUpdate, [in] ParentLink, [in] LocalRotation3D, [out] Rotation3D)
zox_system(ParentPositionSystem, EcsPostUpdate, [in] ParentLink, [in] LocalPosition3D, [out] Position3D)
zoxel_end_module(Transforms3D)

// todo: remove euler use, and find a way to limit quaternion rotations used for camera atm
//      ai mentioned something about using axis and angle of a quaternion

#endif