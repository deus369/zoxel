// i should just set new game state to playing here
// extern void play_game(ecs_world_t *world, ecs_entity_t game);
// extern void end_game(ecs_world_t *world, ecs_entity_t game);
extern ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, float2 anchor);
extern ecs_entity_t spawn_menu_options(ecs_world_t *world, int2 position, float2 anchor);
extern ecs_entity_t main_menu;
extern ecs_entity_t menu_options;
// extern ecs_entity_t local_game;

void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // todo: link ui to game entity
    zox_delete_and_set(main_menu)
    // play_game(world, local_game);
    trigger_event_game(world, local_game, zox_game_playing);
}

void button_event_end_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // end_game(world, local_game);
    trigger_event_game(world, local_game, zox_game_start);
}

void button_event_menu_options(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // todo: link ui to game entity
    zox_delete_and_set(main_menu)
    float2 main_menu_anchor = { 0.5f, 0.5f };
    int2 main_menu_position = int2_zero;
    spawn_menu_options(world, main_menu_position, main_menu_anchor);
}

void button_event_menu_main(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // todo: link ui to game entity
    zox_delete_and_set(menu_options)
    // zox_log("todo: return to options ui")
    float2 main_menu_anchor = { 0.5f, 0.5f };
    int2 main_menu_position = int2_zero;
    spawn_main_menu(world, game_name, main_menu_position, main_menu_anchor);
}

void button_event_volume_increase(ecs_world_t *world, ecs_entity_t trigger_entity) {
    if (global_master_volume < global_master_volume_max) {
        global_master_volume += global_master_volume_increment;
        zox_log(" > increased the volume to [%i]\n", global_master_volume)
    }
}

void button_event_volume_decrease(ecs_world_t *world, ecs_entity_t trigger_entity) {
    if (global_master_volume > 0) {
        global_master_volume -= global_master_volume_increment;
        zox_log(" > decreased the volume to [%i]\n", global_master_volume)
    }
}
