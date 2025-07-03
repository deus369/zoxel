#if !defined(zox_mod_stats) && defined(zox_mod_users)
#define zox_mod_stats

#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "ui/ui.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Stats)
    zox_define_components_stats(world);
    zox_define_systems_stats(world);
    spawn_prefabs_stats(world);
    // link to characters
    add_hook_spawned_character3D(&spawn_character_stats);
    // set_prefab_debug_label(world, &get_label_player_stats);
    set_prefab_debug_label(world, &get_label_player_element_links);
zox_end_module(Stats)

#endif