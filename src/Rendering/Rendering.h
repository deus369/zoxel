//! Transforms2D Struct Defines
// Comment out this line when using as DLL
#ifndef Zoxel_Rendering
#define Zoxel_Rendering

// OpenGL
#include "../OpenGL/opengl.h"
#include "../OpenGL/opengl.c"
#include "../OpenGL/OpenGLHelpers.c"
// rendering
#include "Components/Brightness.c"
#include "Systems/RenderSystem.c"

void InitializeRendering(ecs_world_t *world)
{
    ECS_COMPONENT(world, Brightness);
    ECS_SYSTEM(world, RenderSystem, EcsOnUpdate, Position2D, Rotation2D, Scale2D, Brightness);
    // after defining RenderSystem, add this statement:
    /*ecs_system(world, {
        .entity = RenderSystem,
        .query.filter.instanced = true
    });*/
}

#endif