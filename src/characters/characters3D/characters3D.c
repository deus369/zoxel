#ifndef zox_mod_characters3D
#define zox_mod_characters3D

zox_declare_tag(Character3D)
zox_component_entity(Character3DLink)
#include "data/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "terrain/_.c"

void module_dispose_characters3D(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_character3D();
}

zox_begin_module(Characters3D)
    zox_module_dispose(module_dispose_characters3D)
    initialize_hook_spawned_character3D();
    set_character_settings();
    zox_define_tag(Character3D)
    zox_define_component_entity(Character3DLink)
    add_hook_spawned_character3D(&spawn_character_name_label);
    spawn_prefabs_characters3D(world);
    zox_import_module(Characters3DTerrain)
zox_end_module(Characters3D)

#endif