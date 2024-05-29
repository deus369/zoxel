#ifndef zox_mod_characters
#define zox_mod_characters

zox_declare_tag(Character)
zox_component_byte(TriggerActionA)
zox_component_byte(TriggerActionB)
zox_component_entity(CharacterLink)
#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

/*void spawn_prefabs_characters(ecs_world_t *world) {
    spawn_prefabs_characters2D(world);
    spawn_prefabs_characters3D(world);
}*/

void prefabs_add_characters_to_player(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, CharacterLink, { 0 })
    zox_prefab_set(e, CameraLink, { 0 })
}

zox_begin_module(Characters)
zox_define_tag(Character)
zox_define_component_byte(TriggerActionA)
zox_define_component_byte(TriggerActionB)
zox_define_component_entity(CharacterLink)
zox_import_module(Characters2D)
zox_import_module(Characters3D)
prefabs_add_characters_to_player(world, prefab_player);
zoxel_end_module(Characters)

#endif
