void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    ecs_delete(world, ecs_get(world, trigger_entity, ParentLink)->value);
    spawn_generic_event(world, zoxel_event_play_game);
}

extern void stop_playing_game(ecs_world_t *world);
extern ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, float2 anchor, unsigned char is_close_button);

void button_event_stop_playing_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    ecs_delete(world, ecs_get(world, trigger_entity, ParentLink)->value);
    stop_playing_game(world);
    const int edge_buffer = 8 * default_ui_scale;
    const char *game_name = "zoxel";
    float2 window_anchor = { 0.0f, 1.0f };
    int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    spawn_main_menu(world, game_name, window_position, window_anchor, 0);
}