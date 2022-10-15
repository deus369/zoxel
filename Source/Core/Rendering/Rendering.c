#ifndef Zoxel_Rendering
#define Zoxel_Rendering
//! Rendering Module.

#include "Core/RenderingCore.c"

void RenderingImport(ecs_world_t *world)
{
    // printf("Rendering Module Imported.");
    ECS_MODULE(world, Rendering);
    InitializeRenderingCore(world);
}

#endif