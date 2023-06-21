#ifndef zoxel_rendering
#define zoxel_rendering

int tri_count = 0;
float3 fog_color = (float3) { 0.5f, 0.55f, 0.58f };
// float3 fog_color = (float3) { 0.9f, 0.95f, 0.98f };
// float3 fog_color = (float3) { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };
float fog_density = 0.0326f;
#include "data/uint2.c"
// todo: replace this with a render stack, which can easily be used in a camera_render_system
//      > it can also be sorted better for z issues on translucent materials
float4x4 render_camera_matrix; 
float4x4 ui_camera_matrix; 
zox_declare_tag(Mesh)
zox_declare_tag(ElementRender)
zox_byte_component(MeshDirty)
zox_byte_component(TextureDirty)
zox_component(Brightness, float)
zox_byte_component(RenderLod) // The resolution of each chunk, distance to nearest camera
#include "opengl/opengl.c"
#include "core/rendering_core.c"

zox_begin_module(Rendering)
zox_define_tag(Mesh)
zox_define_tag(ElementRender)
zox_define_component(MeshDirty)
zox_define_component(TextureDirty)
zox_define_component(Brightness)
zox_define_component(RenderLod)
if (!headless) {
    zox_import_module(OpenGL)
    zox_import_module(RenderingCore)
}
zoxel_end_module(Rendering)

// todo: use realm cameras instead of singleton data render_camera_matrix

#endif