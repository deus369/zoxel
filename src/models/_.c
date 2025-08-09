#ifndef zoxm_models
#define zoxm_models

zox_tag(Model);
zox_tag(ModelCharacter);
#include "settings/_.c"
#include "spawn/_.c"
#include "systems/_.c"

zox_begin_module(Models)
    zox_define_tag(Model);
    zox_define_tag(ModelCharacter);
    zox_define_systems_models(world);
zox_end_module(Models)

#endif