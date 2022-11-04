#ifndef Zoxel_Rendering
#define Zoxel_Rendering

// used atm for rendering
float4x4 mainCameraMatrix; 
#include "opengl/opengl.c"
#include "core/rendering_core.c"

//! The Rendering Module!
void RenderingImport(ecs_world_t *world)
{
    // printf("rendering Module Imported.");
    ECS_MODULE(world, Rendering);
    ECS_IMPORT(world, OpenGL);
    ECS_IMPORT(world, RenderingCore);
}

#endif