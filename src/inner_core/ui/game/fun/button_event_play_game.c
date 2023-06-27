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

// extern ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, float2 anchor, unsigned char is_close_button);

/*void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    spawn_generic_event(world, zoxel_event_play_game);
}*/

// zox_delete(ecs_get(world, trigger_entity, ParentLink)->value)
/*zox_delete(ecs_get(world, trigger_entity, ParentLink)->value)
const int edge_buffer = 8 * default_ui_scale;
const char *game_name = "zoxel";
float2 window_anchor = { 0.0f, 1.0f };
int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
spawn_main_menu(world, game_name, window_position, window_anchor, 0);*/