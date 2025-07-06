#ifndef zox_mod_zexts
#define zox_mod_zexts

#include "data/_.c"
#include "components/_.c"
#include "util/zigel_util.c"
#include "util/resize_util.c"
#include "prefabs/_.c"
#include "util/zext_util.c"
#include "systems/_.c"

zox_begin_module(Texts)
    define_components_texts(world);
    define_systems_texts(world);
    spawn_prefabs_texts(world);
zox_end_module(Texts)

#endif