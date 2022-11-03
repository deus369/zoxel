#ifndef Zoxel_Transforms3D
#define Zoxel_Transforms3D

// Components
//! A 3D Position component.
zoxel_component(Position, float3);
//! A quaternion rotation.
zoxel_component(Rotation, float4);
//! A Non Uniform 3D Scale.
zoxel_component(Scale, float3);
//! A Uniform scale used generically.
zoxel_component(UniformScale, float);
//! A rotation but kept in euler form.
zoxel_component(Euler, float3);
//! Scales in 2D!
zoxel_component(Matrix, float4x4);
// Systems

//! The Transforms Module.
/**
 *  Used for 3D positioning.
*/
void Transforms3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Transforms3D);
    ECS_COMPONENT_DEFINE(world, Position);
    ECS_COMPONENT_DEFINE(world, Rotation);
    ECS_COMPONENT_DEFINE(world, Scale);
    ECS_COMPONENT_DEFINE(world, UniformScale);
    ECS_COMPONENT_DEFINE(world, Euler);
    // Matrix System
}

#endif