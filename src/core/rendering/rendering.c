#ifndef zoxel_rendering
#define zoxel_rendering

// todo: is_using_vulkan -> render_backend
#define zox_render_backend_headless 0
#define zox_render_backend_opengl 1
#define zox_render_backend_vulkan 2
#define zox_render_backend_directx 3

// todo: create a render stack?
// todo: use realm cameras instead of singleton data render_camera_matrix, ui_camera_matrix
// todo: remove core functions into rendering outer core, make core all the extra data i've got in here

// zoxel_settings
unsigned char render_backend = zox_render_backend_opengl;
unsigned char is_using_vulkan = 0;
unsigned char is_render_fog = 1;
float3 fog_color = (float3) { 0.5f, 0.55f, 0.58f };
float fog_density = 0.0326f;
float get_fog_density() {
    if (is_render_fog) return fog_density;
    else return 0.0f;
}
#include "data/mesh_alignment_types.c"
// zoxel_declare_components
zox_declare_tag(Mesh)
zox_declare_tag(ElementRender)
zox_component_byte(MeshDirty)
zox_component_byte(TextureDirty)
zox_component_byte(MeshAlignment)
zox_component_byte(RenderLod) // The resolution of each chunk, distance to nearest camera
zox_component_byte(RenderDisabled)
zox_component_float(Brightness)
zox_component_float(Alpha)
#include "opengl/opengl.c" // todo: remove use of this
#include "vulkan/vulkan.c"
#include "core/core.c"
#include "basics2D/basics2D.c"
#include "basics3D/basics3D.c"

unsigned char initialize_rendering(ecs_world_t *world) {
    if (headless) return EXIT_SUCCESS;
    if (is_using_vulkan) return initialize_vulkan(world); // SDL_WINDOW_VULKAN
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
zox_define_component_byte(MeshDirty)
zox_define_component_byte(TextureDirty)
zox_define_component_byte(MeshAlignment)
zox_define_component_byte(RenderLod)
zox_define_component_byte(RenderDisabled)
zox_define_component_float(Brightness)
zox_define_component_float(Alpha)
// zoxel_import_modules
if (!headless) {
    check_vulkan_suppport();
    if (is_using_vulkan) { zox_import_module(Vulkan) }
    else { zox_import_module(OpenGL) }
    zox_import_module(RenderingCore)
    zox_import_module(RenderingBasics2D)
    zox_import_module(RenderingBasics3D)
}
zoxel_end_module(Rendering)

#endif
