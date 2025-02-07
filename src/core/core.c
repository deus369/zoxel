/*
 *  Zox Core
 *
 *      > Maths, Generics, App, Rendering, Files, Etc
 *
 *  The Lowest of the Lows
*/
#ifndef zox_mod_core
#define zox_mod_core

#include "_includes.c"
#include "defines/platform_defines.c"
#include "logs/logs.c"
#include "collections/collections.c"
#include "maths/maths.c"
#include "platforms/platforms.c"
#include "terminals/terminals.c"
#include "ecs/ecs.c"
#include "pathing/pathing.c"

zox_begin_module(Core)
    clear_zoxel_log();
    if (initialize_pathing() == EXIT_FAILURE) {
        zox_log(" ! FAILED PATHING\n")
        return;
    }
    set_noise_seed(get_unique_time_seed());
    #if zoxel_on_web
        add_to_update_loop(update_web_canvas);
    #endif
zoxel_end_module(Core)

/*#ifdef __WINE__
 z ox_*log("  > inside wine\n")
 exit(0)
 #endif*/

#endif
