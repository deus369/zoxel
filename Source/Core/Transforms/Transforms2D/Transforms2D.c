#ifndef Zoxel_Transforms2D
#define Zoxel_Transforms2D

// Components
//! A simple 2D position component.
zoxel_component(Position2D, float2);
//! Rotates in 2D!
zoxel_component(Rotation2D, float);
//! Scales in 2D! - put this in Core or TransformShared
zoxel_component(Scale1D, float);
// Util
#include "Util/Transforms2DUtil.c"

//! Used for 2D Transforms positioning.
void Transforms2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Transforms2D);
    ECS_COMPONENT_DEFINE(world, Position2D);
    ECS_COMPONENT_DEFINE(world, Rotation2D);
    ECS_COMPONENT_DEFINE(world, Scale1D);
}
#endif