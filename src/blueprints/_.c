#if !defined(zoxm_blueprints) && defined(zoxm_nodes)
#define zoxm_blueprints

// first we spawn a texture blueprint
// we want one input, one output, one action node
// connected up
// we display them on screen with windows per node
// we display a blueprint with a pannable space, for now we just can limit it to screen

zox_tag(Blueprint);
zox_tag(Bluenode);
zox_tag(Bluelink);
zox_tag(BluenodeInput);
zox_tag(BluenodeAction);
zox_tag(BluenodeOutput);
#include "prefabs/prefabs.c"

zox_begin_module(Blueprints)
    zox_define_tag(Blueprint);
    zox_define_tag(Bluenode);
    zox_define_tag(Bluelink);
    zox_define_tag(BluenodeInput);
    zox_define_tag(BluenodeAction);
    zox_define_tag(BluenodeOutput);
    add_hook_spawn_prefabs(spawn_prefabs_blueprints);
    // test blueprints - spawn like neurals
zox_end_module(Blueprints)

#endif
