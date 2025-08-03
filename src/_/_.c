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
#include "system/_.c"
#include "terminals/_.c"
#include "pathing/_.c"
#include "states/_.c"
#include "settings/_.c"
#include "hooks/_.c"

void module_dispose_core(ecs_world_t *world, void *ctx) {
    (void) world;
    (void) ctx;
    dispose_hook_terminal_command();
    dispose_game_store();
    dispose_hook_files_load();
    dispose_hook_on_boot();
}

void process_arguments_core(ecs_world_t *world, char* args[], int count) {
    (void) world;
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

// sets up resources path per platform - during preload stage
byte initialize_pathing() {
    zox_logv("Threads Support? %s", supports_threads() ? "YES" : "NO");
    zox_logv("Begin Pathing")
    byte pathing_success = EXIT_FAILURE;
#ifdef zox_android
    pathing_success = initialize_pathing_android();
#else
    pathing_success = initialize_pathing_native();
#endif
    return pathing_success;
}

zox_begin_module(Core)
    zox_module_dispose(module_dispose_core)
    clear_logs();
    initialize_update_loop();
    initialize_post_update_loop();
    initialize_hook_terminal_command();
    initialize_hook_files_load();
    initialize_hook_on_boot();
    // hooks
    add_hook_terminal_command(process_arguments_core);
    add_hook_on_boot(on_boot_game_store);
    set_noise_seed(get_unique_time_seed());
#if zox_web
    add_to_update_loop(update_web_canvas);
#endif
zox_end_module(Core)

#endif