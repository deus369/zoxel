#ifndef zoxel_characters2D
#define zoxel_characters2D

const int spawn_characters2D_count = 64;
const int2 character2DTextureSize = { 16, 16 };
zox_declare_tag(Character2D)
zox_component(Character2DLink, ecs_entity_t)
#include "prefabs/character2D.c"
#include "util/spawn_many.c"
#include "systems/bob_spawn_system.c"

zox_begin_module(Characters2D)
zox_define_tag(Character2D)
zox_define_component(Character2DLink)
spawn_prefab_character2D(world, character2DTextureSize);
#ifdef zoxel_test_character2Ds
spawn_many_characters2D();
#endif
zoxel_end_module(Characters2D)

#endif