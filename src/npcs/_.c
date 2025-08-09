#if !defined(zoxm_ai) && defined(zoxm_characters)
#define zoxm_ai

// todo: a threat level - if you are higher level than npc they should have higher chance to flee!

#include "cmp/_.c"
#include "states/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "util/_.c"

zox_begin_module(Npcs)
    define_components_npcs(world);
    define_systems_npcs(world);
    add_hook_spawn_prefabs(spawn_prefabs_npcs);
zox_end_module(Npcs)

#endif
