#ifndef zox_characters2D
#define zox_characters2D

const int spawn_characters2D_count = 64;
const int2 character2DTextureSize = { 16, 16 };
zox_declare_tag(Character2D)
zox_component_entity(Character2DLink)
#include "prefabs/character2D.c"
#include "util/spawn_many.c"
#include "systems/bob_spawn_system.c"

void spawn_prefabs_characters2D(ecs_world_t *world) {
    spawn_prefab_character2D(world, character2DTextureSize);
#ifdef zoxel_test_character2Ds
    spawn_many_characters2D();
#endif
}

zox_begin_module(Characters2D)
zox_define_tag(Character2D)
zox_define_component_entity(Character2DLink)
zoxel_end_module(Characters2D)

#endif
