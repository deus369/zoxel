#ifndef Zoxel_Rendering
#define Zoxel_Rendering
//! Rendering Module.

#include "OpenGL/OpenGL.c"
#include "Core/RenderingCore.c"

void RenderingImport(ecs_world_t *world)
{
    // printf("Rendering Module Imported.");
    ECS_MODULE(world, Rendering);
    ECS_IMPORT(world, OpenGL);
    ECS_IMPORT(world, RenderingCore);
}

#endif