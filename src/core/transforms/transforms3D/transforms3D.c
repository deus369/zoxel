#ifndef zoxel_transforms3D
#define zoxel_transforms3D

// EcsPostUpdate | EcsPreStore
#define zox_transforms_stage EcsPreStore
// zoxel_component_includes
zox_declare_tag(EulerOverride)
zox_component_float3(Position3D)
zox_component_float3(LastPosition3D)
zox_component_float4(Rotation3D)     // A quaternion rotation
zox_component_float3(Scale)          // A Non Uniform 3D Scale
zox_component(Matrix, float4x4)       // A matrix used for rendering
zox_component_float3(Euler)          // A rotation but kept in euler form
zox_component_float2(EulerLimitX)    // a limitation of euler x axis
zox_component_float2(EulerLimitZ)    // a limitation of euler z axis
zox_component_float3(LocalPosition3D)
zox_component_float4(LocalRotation3D)
// zoxel_util_includes
#include "util/transform3d_util.c"
// zoxel_system_includes
#include "systems/euler_override_system.c"
#include "systems/parent_position_system.c"
#include "systems/parent_rotation_system.c"
#include "systems/euler_limit_x_system.c"
#include "systems/euler_limit_z_system.c"

zox_begin_module(Transforms3D)
// zoxel_component_defines
zox_define_tag(EulerOverride)
zox_define_component_float3(Position3D)
zox_define_component_float3(LastPosition3D)
zox_define_component_float4(Rotation3D)
zox_define_component_float3(Scale)
zox_define_component(Matrix)
zox_define_component_float3(Euler)
zox_define_component_float2(EulerLimitX)
zox_define_component_float2(EulerLimitZ)
zox_define_component_float3(LocalPosition3D)
zox_define_component_float4(LocalRotation3D)
// zoxel_system_defines
zox_system(EulerLimitXSystem, EcsOnUpdate, [in] EulerLimitX, [out] Euler)
zox_system(EulerLimitZSystem, EcsOnUpdate, [in] EulerLimitZ, [out] Euler)
zox_system(EulerOverrideSystem, EcsOnUpdate, [none] EulerOverride, [in] Euler, [out] Rotation3D)
zox_system(ParentRotationSystem, zox_transforms_stage, [in] ParentLink, [in] LocalRotation3D, [out] Rotation3D)
zox_system(ParentPositionSystem, zox_transforms_stage, [in] ParentLink, [in] LocalPosition3D, [out] Position3D)
zoxel_end_module(Transforms3D)

#endif
