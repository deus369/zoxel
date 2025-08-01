#ifndef zox_mod_sdl
#define zox_mod_sdl

#include "components/_.c"
#include "data/_.c"
#include "wrapper/_.c"
#include "settings/_.c"
#include "prefabs/app.c"
#include "inputs/_.c"
#include "util/_.c"

zox_begin_module(Sdl)
    define_components_sdl(world);
    // init
    zox_module_dispose(dispose_apps_sdl);
    // hooks
    add_to_update_loop(update_sdl);
    add_to_post_update_loop(app_update_gpu);
    add_hook_terminal_command(process_terminal_sdl);
    // set_app_screen_resize(world, prefab_app_sdl, screen_dimensions);
    // prefabs
    prefab_app_sdl = spawn_prefab_app_sdl(world);
    // sub module
    zox_import_module(SdlInputs)
zox_end_module(Sdl)

#endif
