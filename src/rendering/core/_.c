#ifndef zox_rendering_core
#define zox_rendering_core

#include "data/settings.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"

void process_arguments_rendering(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "-e") == 0 || strcmp(args[i], "--opengles") == 0) {
            override_opengl_es = 1;
        } else if (strcmp(args[i], "-v") == 0 || strcmp(args[i], "--vulkan") == 0) {
            render_backend = zox_render_backend_vulkan;
        }
    }
}

void dispose_rendering_core(ecs_world_t *world, void *ctx) {
    dispose_render_loop();
    dispose_gpu_systems();
    dispose_hook_load_shader();
}

zox_begin_module(RenderingCore)
    // init
    initialize_render_loop();
    initialize_hook_load_shader();
    initialize_gpu_systems();
    // ecs defines
    define_components_rendering_core(world);
    define_systems_rendering(world);
    // hooks
    add_hook_terminal_command(process_arguments_rendering);
    zox_module_dispose(dispose_rendering_core)
    // prefab spawning
    spawn_prefabs_rendering_core(world);
zox_end_module(RenderingCore)

#endif