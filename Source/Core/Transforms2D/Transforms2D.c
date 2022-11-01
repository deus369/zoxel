//! Transforms2D Struct Defines
// Comment out this line when using as DLL
#ifndef Zoxel_Transforms2D
#define Zoxel_Transforms2D

#include "Components/Position2D.c"
#include "Components/Rotation2D.c"
#include "Components/Scale1D.c"

void Transforms2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Transforms2D);
    ECS_COMPONENT_DEFINE(world, Position2D);
    ECS_COMPONENT_DEFINE(world, Rotation2D);
    ECS_COMPONENT_DEFINE(world, Scale1D);
}

#endif