#ifndef zox_mod_characters
#define zox_mod_characters

zox_component_entity(CharacterLink)
#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

/*void spawn_prefabs_characters(ecs_world_t *world) {
    spawn_prefabs_characters2D(world);
    spawn_prefabs_characters3D(world);
}*/

zox_begin_module(Characters)
zox_define_component_entity(CharacterLink)
zox_import_module(Characters2D)
zox_import_module(Characters3D)
zoxel_end_module(Characters)

#endif
