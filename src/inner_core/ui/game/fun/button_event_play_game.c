#ifdef zoxel_include_players
extern void play_game(ecs_world_t *world);
extern void end_game(ecs_world_t *world);
#endif

void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
#ifdef zoxel_include_players
    play_game(world);
#endif
}

void button_event_end_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
#ifdef zoxel_include_players
    end_game(world);
#endif
}
