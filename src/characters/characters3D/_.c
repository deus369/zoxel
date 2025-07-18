#ifndef zox_mod_characters3D
#define zox_mod_characters3D

// todo: rename zox_declare_tag to zox_tag
zox_declare_tag(Character3D)
zox_declare_tag(SaveCharacter)
zox_component_entity(Character3DLink)
zox_component(CharacterSaveHash, ulong)
#include "data/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"
#include "terrain/_.c"
#include "debug/_.c"
#include "realm/_.c"

void module_dispose_characters3D(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_character3D();
}

zox_begin_module(Characters3D)
    // init -> components -> systems -> hooks
    set_character_settings();
    initialize_hook_spawned_character3D();
    zox_define_tag(Character3D)
    zox_define_tag(SaveCharacter)
    zox_define_component_entity(Character3DLink)
    zox_define_component(CharacterSaveHash)
    zox_system(CharacterSaveSystem, EcsPostUpdate,
        [in] transforms3.Position3D,
        [in] transforms3.Euler,
        [out] CharacterSaveHash,
        [none] SaveCharacter)
    zox_module_dispose(module_dispose_characters3D)
    add_hook_spawned_character3D(&spawn_character_name_label);
    spawn_prefabs_characters3D(world);
    // sub modules
    zox_import_module(Characters3DTerrain)
zox_end_module(Characters3D)

#endif