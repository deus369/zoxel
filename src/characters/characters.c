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

void button_event_jump(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t character = zox_get_value(event->clicker, CharacterLink)
    if (character && can_jump(world, character)) zox_set(character, Jump, { jump_timing })
}

void button_event_attack(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t character = zox_get_value(event->clicker, CharacterLink)
    if (character) zox_set(character, TriggerActionB, { 1 })
}

zox_begin_module(Characters)
    zox_define_tag(Character)
    zox_define_component_byte(TriggerActionA)
    zox_define_component_byte(TriggerActionB)
    zox_define_component_entity(CharacterLink)
    zox_import_module(Characters2D)
    zox_import_module(Characters3D)
    prefabs_add_characters_to_player(world, prefab_player);
zox_end_module(Characters)

#endif
