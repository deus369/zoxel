static inline byte can_jump(ecs_world_t *world, const ecs_entity_t e) {
    return !zox_gett_value(e, DisableMovement) && zox_gett_value(e, Grounded);
}

void button_event_jump(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t character = zox_get_value(event->clicker, CharacterLink)
    if (character && can_jump(world, character)) {
        zox_set(character, Jump, { jump_timing })
    }
}

void button_event_attack(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t character = zox_get_value(event->clicker, CharacterLink)
    if (character) {
        zox_set(character, TriggerActionB, { 1 })
    }
}