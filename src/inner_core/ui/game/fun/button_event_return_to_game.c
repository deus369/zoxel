extern void toggle_pause_ui(ecs_world_t *world);

void button_event_return_to_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    const ParentLink *parentLink = ecs_get(world, trigger_entity, ParentLink);
    ecs_delete(world, parentLink->value);               // destroy main menu
    toggle_pause_ui(world);
}