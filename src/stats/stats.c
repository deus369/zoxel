#if !defined(zox_mod_stats) && defined(zox_mod_users)
#define zox_mod_stats

#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "ui/ui.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Stats)
    define_components_stats(world);
    define_systems_stats(world);
    spawn_prefabs_stats(world);
    // link to characters
    add_hook_spawned_character3D(&spawn_character_stats);
    zox_import_module(StatsUI)
zox_end_module(Stats)

#endif