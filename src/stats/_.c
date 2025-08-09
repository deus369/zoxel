#if !defined(zoxm_stats) && defined(zoxm_users)
#define zoxm_stats

#include "settings/_.c"
#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "ui/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Stats)
    define_components_stats(world);
    define_systems_stats(world);
    add_hook_spawn_prefabs(spawn_prefabs_stats);
    // link to characters
    add_hook_spawned_character3D(&spawn_character_stats);
    zox_import_module(StatsUI)
zox_end_module(Stats)

#endif