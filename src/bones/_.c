#if !defined(zox_mod_bones) && defined(zox_mod_transforms)
#define zox_mod_bones

// #define zox_debug_bones
// #define zox_transparent_skeletons
#include "shaders/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "util/test.c"

zox_begin_module(Bones)
    define_components_bones(world);
    define_systems_bones(world);
    add_hook_load_shader(&spawn_shaders_bones);
    spawn_prefabs_bones(world);
zox_end_module(Bones)

#endif