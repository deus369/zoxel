#ifndef zoxm_characters2D
#define zoxm_characters2D

const int spawn_characters2D_count = 64;
const int2 character2DTextureSize = { 16, 16 };
ecs_entity_t prefab_character2D;
zox_tag(Character2D);
zoxc_entity(Character2DLink);
#include "prefabs/character2D.c"
#include "util/spawn_many.c"
#include "systems/bob_spawn_system.c"

void spawn_prefabs_characters2D(ecs_world_t *world) {
    prefab_character2D = spawn_prefab_character2D(world);
}

zox_begin_module(Characters2)
    zox_define_tag(Character2D);
    zox_define_component_entity(Character2DLink);
    add_hook_spawn_prefabs(spawn_prefabs_characters2D);
zox_end_module(Characters2)

#endif
