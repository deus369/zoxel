#ifndef zoxm_characters
#define zoxm_characters

#include "data/settings.c"
zox_declare_tag(Character)
zox_declare_tag(SilentJumper)
zox_component_byte(CanJump)
zox_component_byte(JumpState)
zox_component_double(Jump)
zox_component_entity(CharacterLink)
// todo: move these to inputs
zox_component_byte(TriggerActionA)
zox_component_byte(TriggerActionB)
zox_memory_component(CharacterLinks, ecs_entity_t)
#include "util/_.c"
#include "jump/systems/_.c"
#include "characters2/_.c"
#include "characters3/_.c"
#include "util/buttons.c"

zox_begin_module(Characters)
    zox_define_tag(Character)
    zox_define_tag(SilentJumper)
    zox_define_component_byte(CanJump)
    zox_define_component_byte(JumpState)
    zox_define_component_double(Jump)
    zox_define_component_byte(TriggerActionA)
    zox_define_component_byte(TriggerActionB)
    zox_define_component_entity(CharacterLink)
    zox_define_memory_component(CharacterLinks)
    // hooks
    add_hook_terminal_command(process_arguments_characters);
    // prefabs
    prefabs_add_characters_to_player(world, prefab_player);
    if (prefab_camera_game) {
        zox_prefab_set(prefab_camera_game, CharacterLink, { 0 })
    }
    define_systems_jump(world);
    zox_import_module(Characters2)
    zox_import_module(Characters3)
zox_end_module(Characters)

#endif
