//! Rendering Module.
#ifndef Zoxel_Rendering
#define Zoxel_Rendering

// OpenGL
#include "../OpenGL/opengl.h"
#include "../OpenGL/opengl.c"
#include "../OpenGL/OpenGLHelpers.c"
// Rendering
#include "Components/Brightness.c"
#include "Systems/RenderSystem.c"

void InitializeRendering(ecs_world_t *world)
{
    ECS_COMPONENT(world, Brightness);
    ECS_SYSTEM(world, RenderSystem, EcsOnUpdate, Position2D, Rotation2D, Scale2D, Brightness);
}

#endif