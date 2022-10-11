//! Transforms2D Struct Defines
// Comment out this line when using as DLL
#ifndef Zoxel_Transforms2D
#define Zoxel_Transforms2D

#include "Components/Position2D.c"
#include "Components/Rotation2D.c"
#include "Components/Scale2D.c"

void InitializeTransforms2D(ecs_world_t *world)
{
    ECS_COMPONENT(world, Position2D);
    ECS_COMPONENT(world, Rotation2D);
    ECS_COMPONENT(world, Scale2D);
}

#endif