#if !defined(zox_mod_blueprints) && defined(zox_mod_nodes)
#define zox_mod_blueprints

// first we spawn a texture blueprint
// we want one input, one output, one action node
// connected up
// we display them on screen with windows per node
// we display a blueprint with a pannable space, for now we just can limit it to screen

zox_declare_tag(Blueprint)
zox_declare_tag(Bluenode)
zox_declare_tag(Bluelink)
zox_declare_tag(BluenodeInput)
zox_declare_tag(BluenodeAction)
zox_declare_tag(BluenodeOutput)
#include "prefabs/prefabs.c"

zox_begin_module(Blueprints)
zox_define_tag(Blueprint)
zox_define_tag(Bluenode)
zox_define_tag(Bluelink)
zox_define_tag(BluenodeInput)
zox_define_tag(BluenodeAction)
zox_define_tag(BluenodeOutput)
spawn_prefabs_blueprints(world);
// test blueprints - spawn like neurals
zoxel_end_module(Blueprints)

#endif
