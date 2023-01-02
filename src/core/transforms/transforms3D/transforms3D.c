#ifndef zoxel_transforms3D
#define zoxel_transforms3D

zoxel_declare_tag(EulerOverride)
zoxel_component(Position, float3)       //! A 3D Position component.
zoxel_component(Rotation, float4)       //! A quaternion rotation.
zoxel_component(Scale, float3)          //! A Non Uniform 3D Scale.
zoxel_component(UniformScale, float)    //! A Uniform scale used generically.
zoxel_component(Euler, float3)          //! A rotation but kept in euler form.
zoxel_component(Matrix, float4x4)       //! A matrix used for rendering.
#include "util/transform3d_util.c"
#include "systems/euler_override_system.c"

//! The transforms Module.
void Transforms3DImport(ecs_world_t *world)
{
    zoxel_module(Transforms3D)
    zoxel_define_tag(EulerOverride)
    zoxel_define_component(Position)
    zoxel_define_component(Rotation)
    zoxel_define_component(Scale)
    zoxel_define_component(UniformScale)
    zoxel_define_component(Euler)
    zoxel_system(world, EulerOverrideSystem, EcsOnUpdate, [none] EulerOverride, [in] Euler, [out] Rotation);
}
#endif