extern void pause_resume(ecs_world_t *world, const ecs_entity_t player);

void button_event_return_to_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    pause_resume(world, player);
}
