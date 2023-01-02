#ifndef zoxel_characters2D
#define zoxel_characters2D

const int spawnCharacter2DsCount = 64;
const int2 character2DTextureSize = { 16, 16 };
zoxel_declare_tag(Character2D)
zoxel_component(Character2DLink, ecs_entity_t)
#include "prefabs/character2D.c"
#include "util/character2D.c"
#include "util/spawn_many.c"
#include "systems/BobSpawnSystem.c"

//! A module for 2 dimensional characters.
void Characters2DImport(ecs_world_t *world)
{
    zoxel_module(Characters2D)
    zoxel_define_tag(Character2D)
    zoxel_define_component(Character2DLink)
    spawn_prefab_character2D(world, character2DTextureSize);
    #ifdef zoxel_test_character2Ds
    spawn_many_characters();
    #endif
}
#endif