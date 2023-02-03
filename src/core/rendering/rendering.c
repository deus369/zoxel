#ifndef zoxel_rendering
#define zoxel_rendering

// stats
int quad_count = 0;
#include "data/GLuint2.c"
// used atm for rendering
float4x4 main_camera_matrix; 
float4x4 ui_camera_matrix; 
float4x4 main_camera_matrix2;
zoxel_declare_tag(Mesh)
zoxel_declare_tag(ElementRender)
zoxel_byte_component(MeshDirty)
zoxel_component(Brightness, float)
#include "opengl/opengl.c"
#include "core/rendering_core.c"

//! The Rendering Module!
void RenderingImport(ecs_world_t *world)
{
    zoxel_module(Rendering)
    zoxel_define_tag(Mesh)
    zoxel_define_tag(ElementRender)
    zoxel_define_component(Brightness)
    zoxel_define_component(MeshDirty)
    if (!headless)
    {
        zoxel_import_module(OpenGL)
        zoxel_import_module(RenderingCore)
    }
}
#endif