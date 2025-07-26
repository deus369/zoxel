#ifndef zox_mod_rendering
#define zox_mod_rendering

#include "components/_.c"
#include "data/_.c"
#include "settings/_.c"

#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"

#include "shaders/_.c"
#include "basics2D/_.c"
#ifndef zox_disable_rendering3D
    #include "basics3D/_.c"
#endif
#include "cameras/_.c"
#include "debug/_.c"

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
    // init
    initialize_render_loop();
    initialize_hook_load_shader();
    initialize_gpu_systems();
    // ecs defines
    define_components_rendering(world);
    define_systems_rendering(world);
    // hooks
    add_hook_terminal_command(process_arguments_rendering);
    zox_module_dispose(on_module_dispose_rendering)
    // prefab spawning
    spawn_prefabs_rendering_core(world);


    zox_import_module(Shaders)
    zox_import_module(Rendering2)
#ifdef zox_mod_rendering_basics3D
    zox_import_module(Rendering3)
#endif
    zox_import_module(RenderingCameras)
    zox_module_dispose(dispose_rendering)
    add_to_update_loop(viewport_clear);
    initialize_settings_rendering(world);
    if (prefab_camera_game) {
        zox_prefab_set(prefab_camera_game, FrameBufferLink, { 0 })
        zox_prefab_set(prefab_camera_game, RenderBufferLink, { 0 })
    }
zox_end_module(Rendering)

#endif