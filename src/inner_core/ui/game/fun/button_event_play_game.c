void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    ecs_delete(world, ecs_get(world, trigger_entity, ParentLink)->value);
    spawn_generic_event(world, zoxel_event_play_game);
}

extern void stop_playing_game(ecs_world_t *world);
extern ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, int2 window_size, float2 anchor, unsigned char is_close_button);

void button_event_stop_playing_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    ecs_delete(world, ecs_get(world, trigger_entity, ParentLink)->value);
    stop_playing_game(world);
    const int edge_buffer = 8 * default_ui_scale;
    const char *game_name = "zoxel";
    int2 window_size = { 260, 220 };
    float2 window_anchor = { 0.0f, 1.0f };
    int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    spawn_main_menu(world, game_name, window_position, window_size, window_anchor, 0);
}

/*void PlayGameButtonSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++) {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1) {
            const ParentLink *parentLink = ecs_get(world, it->entities[i], ParentLink);
            ecs_entity_t window = parentLink->value;
            ecs_delete(it->world, window);
            spawn_generic_event(it->world, zoxel_event_play_game);
        }
    }
}
zoxel_declare_system(PlayGameButtonSystem)*/