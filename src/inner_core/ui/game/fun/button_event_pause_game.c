extern ecs_entity_t main_player;
extern void toggle_pause_ui(ecs_world_t *world, ecs_entity_t player);

void button_event_pause_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    toggle_pause_ui(world, main_player);
}
