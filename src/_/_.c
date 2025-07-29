/*
 *  Zox Core
 *
 *      > Maths, Generics, App, Rendering, Files, Etc
 *
 *  The Lowest of the Lows
 */
#ifndef zox_mod_core
#define zox_mod_core

#include "platforms/defines.c"
#include "platforms/_.c"
#include "terminals/_.c"
#include "pathing/_.c"
#include "states/_.c"
#include "settings/_.c"

void module_dispose_core(ecs_world_t *world, void *ctx) {
    dispose_hook_terminal_command();
}

void process_arguments_core(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (!strcmp(args[i], "--fps")) {
            target_fps = (byte) (atoi(args[i + 1]));
            i++;
        } else if (!strcmp(args[i], "--singlethread")) {
            is_multithreading = 0;
        } else if (!strcmp(args[i], "-p") || !strcmp(args[i], "--profiler")) {
            profiler = 1;
        }
    }
}

zox_begin_module(Core)
    zox_module_dispose(module_dispose_core)
    clear_logs();
    initialize_update_loop();
    initialize_post_update_loop();
    initialize_hook_terminal_command();
    add_hook_terminal_command(process_arguments_core);
    byte pathing_success = EXIT_FAILURE;
#ifdef zox_android
    pathing_success = initialize_pathing_android();
#else
    pathing_success = initialize_pathing();
#endif
    if (pathing_success == EXIT_FAILURE) {
        zox_log_error("pathing failed")
        return;
    } else {
        set_noise_seed(get_unique_time_seed());
#if zoxel_on_web
        add_to_update_loop(update_web_canvas);
#endif
    }
zox_end_module(Core)

#endif