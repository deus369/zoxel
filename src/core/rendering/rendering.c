#ifndef zoxel_rendering
#define zoxel_rendering

// todo: create a render stack?
// todo: use realm cameras instead of singleton data render_camera_matrix, ui_camera_matrix
// todo: remove core functions into rendering outer core, make core all the extra data i've got in here

// zoxel_settings
int tri_count = 0;
unsigned char is_render_fog = 1;
float3 fog_color = (float3) { 0.5f, 0.55f, 0.58f };
float fog_density = 0.0326f;
float get_fog_density() {
    if (is_render_fog) return fog_density;
    else return 0.0f;
}
#include "data/mesh_alignment_types.c"
// todo: replace this with a render stack, which can easily be used in a camera_render_system
//      > it can also be sorted better for z issues on translucent materials
float4x4 render_camera_matrix; 
// float4x4 ui_camera_matrix; 
// zoxel_declare_components
// todo: move these to 'core', make core load despite opengl, before it
zox_declare_tag(Mesh)
zox_declare_tag(ElementRender)
zox_byte_component(MeshDirty)
zox_byte_component(TextureDirty)
zox_component(Brightness, float)
zox_byte_component(MeshAlignment)
zox_byte_component(RenderLod) // The resolution of each chunk, distance to nearest camera
#include "opengl/opengl.c"
#include "vulkan/vulkan.c"
#include "core/rendering_core.c"
#include "basics3D/basics3D.c"

extern unsigned char is_vulkan;

unsigned char initialize_rendering(ecs_world_t *world) {
    if (headless) return EXIT_SUCCESS;
    if (is_vulkan) return initialize_vulkan(world); // SDL_WINDOW_VULKAN
    else return initialize_opengl(world);
}

void on_close_rendering(ecs_world_t *world) {
    opengl_dispose_shaders();
}

void spawn_prefabs_rendering(ecs_world_t *world) {
    spawn_prefabs_rendering_core(world);
}

zox_begin_module(Rendering)
// zoxel_define_components
zox_define_tag(Mesh)
zox_define_tag(ElementRender)
zox_define_component(MeshDirty)
zox_define_component(TextureDirty)
zox_define_component(Brightness)
zox_define_component(MeshAlignment)
zox_define_component(RenderLod)
// zoxel_import_modules
if (!headless) {
    if (is_vulkan) { zox_import_module(Vulkan) }
    else { zox_import_module(OpenGL) }
    zox_import_module(RenderingCore)
    zox_import_module(RenderingBasics3D)
}
zoxel_end_module(Rendering)

#endif