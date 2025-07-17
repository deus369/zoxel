#ifndef zox_mod_characters
#define zox_mod_characters

#include "data/settings.c"
zox_declare_tag(Character)
zox_component_entity(CharacterLink)
// todo: move these to inputs
zox_component_byte(TriggerActionA)
zox_component_byte(TriggerActionB)
#include "util/prefabs.c"
#include "characters2D/_.c"
#include "characters3D/_.c"
#include "util/buttons.c"

zox_begin_module(Characters)
    add_hook_terminal_command(process_arguments_characters);
    zox_define_tag(Character)
    zox_define_component_byte(TriggerActionA)
    zox_define_component_byte(TriggerActionB)
    zox_define_component_entity(CharacterLink)
    zox_import_module(Characters2D)
    zox_import_module(Characters3D)
    prefabs_add_characters_to_player(world, prefab_player);
    zox_prefab_set(prefab_camera_game, CharacterLink, { 0 })
zox_end_module(Characters)

#endif
