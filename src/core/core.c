/*
 *  Zox Core
 *
 *      > Maths, Generics, App, Rendering, Files, Etc
 *
 *  The Lowest of the Lows
*/
#ifndef zox_mod_core
#define zox_mod_core

// base libraries we rely on besides ecs
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror

// base util functions and types
//      todo: move these to core folder
#include "defines/platform_defines.c"
#include "logs/logs.c"
#include "collections/collections.c"
#include "maths/maths.c"
#include "platforms/platforms.c"
#include "terminals/terminals.c"
#include "ecs/ecs.c"

zox_begin_module(Core)
    clear_zoxel_log();
    // other calls
    set_noise_seed(get_unique_time_seed());
    #if zoxel_on_web
        add_to_update_loop(update_web_canvas);
    #endif
zoxel_end_module(Core)

#endif
