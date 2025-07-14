#ifndef zox_mod_rendering
#define zox_mod_rendering

// #define zox_disable_rendering3D
#define render_lod_uninitialized 255
#define render_lod_invisible 254
byte rendering_initialized = 0;
#include "data/renderer_types.c"
#include "data/mesh_alignment_types.c"
#include "data/settings.c"
#include "data/mesh_states.c"
zox_declare_tag(Mesh)
zox_component_byte(MeshDirty)
zox_component_entity(MeshLink)
zox_component_byte(TextureDirty)
zox_component_byte(MeshAlignment)
zox_component_byte(RenderLod)
zox_component_byte(RenderDistance)
zox_component_byte(RenderDisabled)
zox_component_float(Brightness)
zox_component_float(Alpha)
zox_component_entity(MaterialLink)
zox_increment_system_with_reset(MeshDirty, mesh_state_end)
#include "opengl/_.c"
#include "vulkan/_.c"
#include "core/_.c"
#include "shaders/_.c"
#include "basics2D/_.c"
#ifndef zox_disable_rendering3D
    #include "basics3D/_.c"
#endif
#include "cameras/_.c"

void viewport_clear(ecs_world_t *world) {
    opengl_clear(color_rgb_to_float3(viewport_clear_color));
}

byte initialize_rendering(ecs_world_t *world) {
    if (headless) {
        return EXIT_SUCCESS;
    } else if (render_backend == zox_render_backend_opengl) {
        rendering_initialized = 1;
        return initialize_opengl(world);
    } else if (render_backend == zox_render_backend_vulkan) {
        rendering_initialized = 1;
        return initialize_vulkan(world); // SDL_WINDOW_VULKAN
    } else {
        zox_log_error("! unknown render_backend")
        return EXIT_FAILURE;
    }
}

void dispose_rendering(ecs_world_t *world, void *ctx) {
    if (headless) {
        return;
    }
    dispose_vulkan(world);
}

zox_begin_module(Rendering)
    zox_module_dispose(dispose_rendering)
    zox_define_tag(Mesh)
    zox_define_component_byte(MeshDirty)
    zox_define_component_byte(MeshAlignment)
    zox_define_component_entity(MeshLink)
    zox_define_component_byte(TextureDirty)
    zox_define_component_byte(RenderLod)
    zox_define_component_byte(RenderDistance)
    zox_define_component_byte(RenderDisabled)
    zox_define_component_float(Brightness)
    zox_define_component_float(Alpha)
    zox_define_component_entity(MaterialLink)
    zox_define_increment_system(MeshDirty, EcsOnLoad)
    if (render_backend == zox_render_backend_headless) {
        return;
    } else if (render_backend == zox_render_backend_vulkan && check_vulkan_suppport()) {
        zox_import_module(Vulkan)
    }
    zox_import_module(RenderingCore)
    zox_import_module(Shaders)
    zox_import_module(RenderingBasics2D)
#ifdef zox_mod_rendering_basics3D
    zox_import_module(RenderingBasics3D)
#endif
    zox_import_module(RenderingCameras)
    add_to_update_loop(viewport_clear);
zox_end_module(Rendering)

#endif