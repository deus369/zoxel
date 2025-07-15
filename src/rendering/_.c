#ifndef zox_mod_rendering
#define zox_mod_rendering

#include "components/_.c"
#include "data/_.c"
#include "settings/_.c"
zox_increment_system_with_reset(MeshDirty, mesh_state_end)
// #include "opengl/_.c"
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
    define_components_rendering(world);
    zox_define_increment_system(MeshDirty, EcsOnLoad)
    zox_import_module(RenderingCore)
    zox_import_module(Shaders)
    zox_import_module(RenderingBasics2D)
#ifdef zox_mod_rendering_basics3D
    zox_import_module(RenderingBasics3D)
#endif
    zox_import_module(RenderingCameras)
    zox_module_dispose(dispose_rendering)
    add_to_update_loop(viewport_clear);
zox_end_module(Rendering)

#endif