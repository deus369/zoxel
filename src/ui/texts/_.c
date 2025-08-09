#ifndef zoxm_zexts
#define zoxm_zexts

// todo: move labels to here as prefab
#include "data/_.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"

zox_begin_module(Texts)
    define_components_texts(world);
    define_systems_texts(world);
    add_hook_spawn_prefabs(spawn_prefabs_texts);
zox_end_module(Texts)

#endif