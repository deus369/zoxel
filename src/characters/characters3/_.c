#ifndef zoxm_characters3
#define zoxm_characters3

// todo: rename zox_tag to zox_tag
byte disable_npc_uis = 0;
byte disable_npc_hooks = 0;
byte disable_npc_positioner = 0;
#include "settings/_.c"
#include "components/_.c"
#include "states/_.c"
#include "data/_.c"
#include "prefabs/_.c"
#include "spawn/_.c"
#include "util/_.c"
#include "systems/_.c"
#include "terrain/_.c"
#include "debug/_.c"
#include "realm/_.c"

void module_dispose_characters3D(ecs_world_t *world, void *ctx) {
    (void) world;
    (void) ctx;
    dispose_hook_spawned_character3D();
}

zox_begin_module(Characters3)
    define_components_characters3(world);
    define_systems_characters3(world);
    // init
    set_character_settings();
    initialize_hook_spawned_character3D();
    // hooks
    zox_module_dispose(module_dispose_characters3D)
    add_hook_spawned_character3D(&spawn_character_name_label);
    add_hook_spawn_prefabs(spawn_prefabs_characters3D);
    // sub modules
    zox_import_module(Characters3Terrain)
zox_end_module(Characters3)

#endif