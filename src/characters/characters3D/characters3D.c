#ifndef zox_mod_characters3D
#define zox_mod_characters3D

zox_declare_tag(Character3D)
zox_component_entity(Character3DLink)
#include "data/settings.c"
#include "data/hooks.c"
#include "data/spawn_character3D_data.c"
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "terrain/characters3D_terrain.c"

void module_dispose_characters3D(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_character3D();
}

zox_begin_module(Characters3D)
    zox_module_dispose(module_dispose_characters3D)
    initialize_hook_spawned_character3D();
    add_hook_spawned_character3D(&spawn_character_name_label);
    set_character_settings();
    zox_define_tag(Character3D)
    zox_define_component_entity(Character3DLink)
    spawn_prefabs_characters3D(world);
    zox_import_module(Characters3DTerrain)
zox_end_module(Characters3D)

#endif
