#ifndef zoxm_sdl
#define zoxm_sdl

#include "components/_.c"
#include "data/_.c"
#include "wrapper/_.c"
#include "settings/_.c"
#include "prefabs/app.c"
#include "inputs/_.c"
#include "util/_.c"

void spawn_prefabs_sdl(ecs_world_t* world) {
    prefab_app_sdl = spawn_prefab_app_sdl(world);
}

zox_begin_module(Sdl)
    define_components_sdl(world);
    // init
    zox_module_dispose(dispose_apps_sdl);
    // hooks
    add_to_update_loop(update_sdl);
    add_to_post_update_loop(app_update_gpu);
    add_hook_terminal_command(process_terminal_sdl);
    add_hook_spawn_prefabs(spawn_prefabs_sdl);
    zox_import_module(SdlInputs)
zox_end_module(Sdl)

#endif
