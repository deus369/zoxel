#ifndef zoxel_characters
#define zoxel_characters

zox_component(CharacterLink, ecs_entity_t)
#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

void spawn_prefabs_characters(ecs_world_t *world) {
    spawn_prefabs_characters2D(world);
    spawn_prefabs_characters3D(world);
}

zox_begin_module(Characters)
zox_define_component(CharacterLink)
zox_import_module(Characters2D)
zox_import_module(Characters3D)
// spawn_prefabs_characters(world);
zoxel_end_module(Characters)

#endif