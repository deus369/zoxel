//! Rendering Module.
#ifndef Zoxel_Rendering
#define Zoxel_Rendering

// OpenGL
#include "../../Imports/OpenGL/opengl.h"
#include "../../Imports/OpenGL/opengl.c"
#include "../../Imports/OpenGL/OpenGLHelpers.c"
// Rendering
#include "Components/Brightness.c"
ECS_COMPONENT_DECLARE(Brightness);
// Systems
#include "Systems/RenderSystem.c"

void RenderingImport(ecs_world_t *world)
{
    ECS_MODULE(world, Rendering);
    ECS_COMPONENT_DEFINE(world, Brightness);
    ECS_SYSTEM(world, RenderSystem, EcsOnUpdate, Position2D, Rotation2D, Scale2D, Brightness);
}

#endif