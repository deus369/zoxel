/*
 *  Zox Core
 *
 *      > Maths, Generics, App, Rendering, Files, Etc
 *
 *  The Lowest of the Lows
 */
#ifndef zox_mod_core
#define zox_mod_core

#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror

#include "platforms/defines.c"
#include "platforms/_.c"
#include "terminals/_.c"
#include "pathing/_.c"

void module_dispose_core(ecs_world_t *world, void *ctx) {
    dispose_hook_terminal_command();
}

void process_arguments_core(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--fps") == 0) {
            target_fps = (byte) (atoi(args[i + 1]));
            i++;
        } else if (strcmp(args[i], "--singlethread") == 0) {
            is_multithreading = 0;
        } else if (strcmp(args[i], "-p") == 0 || strcmp(args[i], "--profiler") == 0) {
            profiler = 1;
        }
    }
}

zox_begin_module(Core)
    zox_module_dispose(module_dispose_core)
    clear_zoxel_log();
    initialize_update_loop();
    initialize_post_update_loop();
    initialize_hook_terminal_command();
    add_hook_terminal_command(process_arguments_core);
    if (initialize_pathing() == EXIT_FAILURE) {
        zox_log(" ! FAILED PATHING\n")
        return;
    } else {
        set_noise_seed(get_unique_time_seed());
        #if zoxel_on_web
        add_to_update_loop(update_web_canvas);
        #endif
    }
zox_end_module(Core)

#endif