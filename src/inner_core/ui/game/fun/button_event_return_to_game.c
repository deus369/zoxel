#ifdef zoxel_include_players
    extern void toggle_pause_ui(ecs_world_t *world);
#endif

void button_event_return_to_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    #ifdef zoxel_include_players
        toggle_pause_ui(world);
    #endif
}