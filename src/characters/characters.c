#ifndef zox_mod_characters
#define zox_mod_characters

unsigned char disable_npcs = 0;
zox_declare_tag(Character)
zox_component_byte(TriggerActionA) // where should these go? Inputs / Triggers - Bindings
zox_component_byte(TriggerActionB)
zox_component_entity(CharacterLink)
#include "util/prefabs.c"
#include "characters2D/characters2D.c"
#include "characters3D/characters3D.c"

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
