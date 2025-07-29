#ifndef zox_mod_sounds
#define zox_mod_sounds

#include "settings/_.c"
#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "io/_.c"
#include "waves/_.c"
#include "util/_.c"
#include "instruments/_.c"
#include "systems/_.c"

zox_begin_module(Sounds)
    // ecs defines
    define_components_sounds(world);
    define_systems_sounds(world);
    // hooks
    zox_module_dispose(dispose_sounds)
    add_hook_terminal_command(process_arguments_sounds);
    add_hook_files_load(load_files_sounds);
    // prefabs
    spawn_prefabs_sounds(world);
    // settings
    initialize_settings_sounds(world);
zox_end_module(Sounds)

#endif