extern ecs_entity_t main_player;
extern void toggle_pause_ui(ecs_world_t *world, ecs_entity_t player);

// from touch_ui
void button_event_pause_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    toggle_pause_ui(world, player);
}
