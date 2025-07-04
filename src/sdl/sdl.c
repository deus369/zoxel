#ifndef zox_sdl
#define zox_sdl

// #define zox_log_screens
// #define zox_log_platform
#include "_import.c" // sdl is here
#include "components/components.c"
#include "prefabs/app_sdl.c"
#include "data/settings.c"
#include "inputs/inputs.c"
#include "util/_.c"

zox_begin_module(Sdl)
    zox_module_dispose(dispose_apps_sdl)
    define_components_sdl(world);
    zox_import_module(SdlInputs)
    initialize_apps_sdl(world);
    // spawn just one prefab
    spawn_prefab_app_sdl(world);
    // attach to loops
    add_to_update_loop(update_sdl);
    add_to_post_update_loop(app_update_gpu);
    set_app_screen_resize(world, prefab_app_sdl, screen_dimensions);
zox_end_module(Sdl)

#endif
