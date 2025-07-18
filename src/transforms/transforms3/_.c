#ifndef zox_mod_transforms3
#define zox_mod_transforms3

#define zox_transforms_stage EcsPreStore // EcsPostUpdate | EcsPreStore
zox_declare_tag(EulerOverride)
zox_declare_tag(CameraTransform)
zox_component_float3(Position3D)
zox_component_float4(Rotation3D)     // A quaternion rotation
zox_component_float3(Scale3D)          // A Non Uniform 3D Scale
zox_component(Matrix, float4x4)       // A matrix used for rendering
zox_component_float3(Euler)          // A rotation but kept in euler form
zox_component_float2(EulerLimitX)    // a limitation of euler x axis
zox_component_float2(EulerLimitZ)    // a limitation of euler z axis
zox_component_float3(LocalPosition3D)
zox_component_float4(LocalRotation3D)
zox_component(TransformMatrix, float4x4)
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Transforms3)
    zox_define_tag(EulerOverride)
    zox_define_tag(CameraTransform)
    zox_define_component_float3(Position3D)
    zox_define_component_float4(Rotation3D)
    zox_define_component_float3(Scale3D)
    zox_define_component(Matrix)
    zox_define_component_float3(Euler)
    zox_define_component_float2(EulerLimitX)
    zox_define_component_float2(EulerLimitZ)
    zox_define_component_float3(LocalPosition3D)
    zox_define_component_float4(LocalRotation3D)
    zox_define_component(TransformMatrix)
    zox_define_systems_transforms3D(world);
zox_end_module(Transforms3)

#endif