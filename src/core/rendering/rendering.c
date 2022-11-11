#ifndef zoxel_rendering
#define zoxel_rendering

// data
#include "data/GLuint2.c"
// used atm for rendering
float4x4 main_camera_matrix; 
float4x4 ui_camera_matrix; 
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