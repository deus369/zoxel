extern ecs_entity_t spawn_main_menu(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const char *header_label, const int2 position, const float2 anchor);
extern ecs_entity_t spawn_menu_options(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor);

void button_event_play_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) return;
    zox_delete_and_set(menu)
    const ecs_entity_t game = zox_get_value(player, GameLink)
    trigger_event_game(world, game, zox_game_playing);
}

void button_event_end_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuPaused, menu)
    if (!menu) return;
    zox_delete_and_set(menu)
    const ecs_entity_t game = zox_get_value(player, GameLink)
    trigger_event_game(world, game, zox_game_start);
}

void button_event_menu_options(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) return;
    zox_delete_and_set(menu)
    spawn_menu_options(world, player, canvas, int2_zero, float2_half);
}

void button_event_menu_main(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuOptions, menu)
    if (menu == 0) return; // failed to find ...
    zox_delete_and_set(menu)
    spawn_main_menu(world, player, canvas, game_name, int2_zero, float2_half);
}

void button_event_volume_increase(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    if (global_master_volume < global_master_volume_max) {
        global_master_volume += global_master_volume_increment;
        zox_log(" > increased the volume to [%i]\n", global_master_volume)
    }
}

void button_event_volume_decrease(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    if (global_master_volume > 0) {
        global_master_volume -= global_master_volume_increment;
        zox_log(" > decreased the volume to [%i]\n", global_master_volume)
    }
}
