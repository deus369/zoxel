#ifndef zox_mod_sounds
#define zox_mod_sounds

#include "settings/_.c"
#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "sdl_mixer.c"
#include "io/_.c"
#include "util/_.c"
#include "instruments/_.c"
#include "systems/_.c"

zox_begin_module(Sounds)
    zox_module_dispose(dispose_sounds)
    define_components_sounds(world);
    define_systems_sounds(world);
    spawn_prefabs_sounds(world);
    initialize_sounds(world);
zox_end_module(Sounds)

#endif