#ifdef zoxel_include_players
extern void toggle_pause_ui(ecs_world_t *world, ecs_entity_t player);
#endif

void button_event_return_to_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
#ifdef zoxel_include_players
    toggle_pause_ui(world, player);
#endif
}
