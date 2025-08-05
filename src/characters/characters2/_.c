#ifndef zoxm_characters2D
#define zoxm_characters2D

const int spawn_characters2D_count = 64;
const int2 character2DTextureSize = { 16, 16 };
ecs_entity_t prefab_character2D;
zox_declare_tag(Character2D)
zox_component_entity(Character2DLink)
#include "prefabs/character2D.c"
#include "util/spawn_many.c"
#include "systems/bob_spawn_system.c"

void spawn_prefabs_characters2D(ecs_world_t *world) {
    prefab_character2D = spawn_prefab_character2D(world, character2DTextureSize);
}

zox_begin_module(Characters2)
    zox_define_tag(Character2D)
    zox_define_component_entity(Character2DLink)
    spawn_prefabs_characters2D(world);
    #ifdef zoxel_test_character2Ds
        spawn_many_characters2D();
    #endif
zox_end_module(Characters2)

#endif
