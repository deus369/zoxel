#ifndef zox_mod_models
#define zox_mod_models

zox_declare_tag(Model)
zox_declare_tag(ModelCharacter)
#include "settings/_.c"
#include "spawn/_.c"
#include "systems/_.c"

zox_begin_module(Models)
    zox_define_tag(Model)
    zox_define_tag(ModelCharacter)
    zox_define_systems_models(world);
zox_end_module(Models)

#endif