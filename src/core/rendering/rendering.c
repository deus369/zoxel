#ifndef zoxel_rendering
#define zoxel_rendering

int tri_count = 0;
float3 fog_color = (float3) { 0.5f, 0.55f, 0.58f };
// float3 fog_color = (float3) { 0.9f, 0.95f, 0.98f };
// float3 fog_color = (float3) { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };
float fog_density = 0.0326f;
#include "data/GLuint2.c"
float4x4 main_camera_matrix; 
float4x4 ui_camera_matrix; 
float4x4 main_camera_matrix2;
zoxel_declare_tag(Mesh)
zoxel_declare_tag(ElementRender)
zoxel_byte_component(MeshDirty)
zoxel_byte_component(TextureDirty)
zoxel_component(Brightness, float)
#include "opengl/opengl.c"
#include "core/rendering_core.c"

zoxel_begin_module(Rendering)
zoxel_define_tag(Mesh)
zoxel_define_tag(ElementRender)
zoxel_define_component(MeshDirty)
zoxel_define_component(TextureDirty)
zoxel_define_component(Brightness)
if (!headless && is_opengl_running()) {
    zoxel_import_module(OpenGL)
    zoxel_import_module(RenderingCore)
}
zoxel_end_module(Rendering)

// todo: use realm cameras instead of singleton data main_camera_matrix

#endif