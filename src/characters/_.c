#ifndef zox_mod_characters
#define zox_mod_characters

#include "data/settings.c"
zox_declare_tag(Character)
zox_component_byte(CanJump)
zox_component_double(Jump)
zox_component_entity(CharacterLink)
// todo: move these to inputs
zox_component_byte(TriggerActionA)
zox_component_byte(TriggerActionB)
zox_memory_component(CharacterLinks, ecs_entity_t)
#include "util/prefabs.c"
#include "characters2D/_.c"
#include "characters3D/_.c"
#include "util/buttons.c"

static inline byte get_character_can_jump(ecs_world_t *world, ecs_entity_t c) {
    return zox_valid(c) && zox_has(c, CanJump) ? zox_gett_value(c, CanJump) : 0;
}
static inline ecs_entity_t get_player_character(ecs_world_t *world, ecs_entity_t p) {
    return zox_valid(p) && zox_has(p, CharacterLink) ? zox_gett_value(p, CharacterLink) : 0;
}

zox_begin_module(Characters)
    zox_define_tag(Character)
    zox_define_component_byte(CanJump)
    zox_define_component_byte(Jump)
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
    zox_import_module(Characters2D)
    zox_import_module(Characters3D)
zox_end_module(Characters)

#endif
