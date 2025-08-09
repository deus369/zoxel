#ifndef zoxm_characters
#define zoxm_characters

#include "data/settings.c"
zox_tag(Character);
zox_tag(SilentJumper);
zoxc_byte(CanJump);
zoxc_byte(JumpState);
zoxc_double(Jump);
zoxc_byte(FlyMode);
zoxc_entity(CharacterLink);
zoxc_arrayd(CharacterLinks, ecs_entity_t)
#include "util/_.c"
#include "jump/systems/_.c"
#include "characters2/_.c"
#include "characters3/_.c"
#include "util/buttons.c"
#include "debug/_.c"

ecs_entity_t get_linked_character(ecs_world_t* world, const ecs_entity_t e) {
    return zox_valid(e) && zox_has(e, CharacterLink) ? zox_gett_value(e, CharacterLink) : 0;
}

void spawn_prefabs_characters(ecs* world) {
    prefabs_add_characters_to_player(world, prefab_player);
    if (prefab_camera_game) {
        zox_prefab_set(prefab_camera_game, CharacterLink, { 0 });
    }
}

zox_begin_module(Characters)
    zox_define_tag(Character);
    zox_define_tag(SilentJumper);
    zox_define_component_byte(CanJump);
    zox_define_component_byte(JumpState);
    zox_define_component_double(Jump);
    zox_define_component_entity(CharacterLink);
    zox_define_memory_component(CharacterLinks);
    zox_define_component_byte(FlyMode);
    add_hook_spawn_prefabs(spawn_prefabs_characters);
    // hooks
    add_hook_terminal_command(process_arguments_characters);
    define_systems_jump(world);
    zox_import_module(Characters2);
    zox_import_module(Characters3);
zox_end_module(Characters)

#endif
