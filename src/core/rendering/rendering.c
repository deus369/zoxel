#ifndef zoxel_rendering
#define zoxel_rendering

// data
#include "data/GLuint2.c"
// used atm for rendering
float4x4 main_camera_matrix; 
float4x4 ui_camera_matrix; 
float4x4 main_camera_matrix2;
// shared tags
ECS_DECLARE(Mesh);
ECS_DECLARE(ElementRender);
// shared components
zoxel_state_component(MeshDirty);
zoxel_component(EternalRotation, float4);
zoxel_component(Brightness, float);
// sub modules
#include "opengl/opengl.c"
#include "core/rendering_core.c"

//! The Rendering Module!
void RenderingImport(ecs_world_t *world)
{
    zoxel_module(Rendering)
    ECS_TAG_DEFINE(world, Mesh);
    ECS_TAG_DEFINE(world, ElementRender);
    ECS_COMPONENT_DEFINE(world, Brightness);
    ECS_COMPONENT_DEFINE(world, MeshDirty);
    ECS_COMPONENT_DEFINE(world, EternalRotation);
    if (!headless)
    {
        ECS_IMPORT(world, OpenGL);
        ECS_IMPORT(world, RenderingCore);
    }
}
#endif