extern ecs_entity_t spawn_main_menu(ecs_world_t *world, const ecs_entity_t canvas, const char *header_label, const int2 position, const float2 anchor);
extern ecs_entity_t spawn_menu_options(ecs_world_t *world, const ecs_entity_t canvas, const int2 position, const float2 anchor);

void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    const ecs_entity_t canvas = zox_get_value(trigger_entity, CanvasLink)
    find_child_with_tag(canvas, MenuMain, found_child)
    if (!found_child) return;
    zox_delete_and_set(found_child)
    trigger_event_game(world, local_game, zox_game_playing);
}

void button_event_end_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    trigger_event_game(world, local_game, zox_game_start);
}

void button_event_menu_options(ecs_world_t *world, ecs_entity_t trigger_entity) {
    const ecs_entity_t canvas = zox_get_value(trigger_entity, CanvasLink)
    find_child_with_tag(canvas, MenuMain, found_child)
    if (!found_child) return;
    zox_delete_and_set(found_child)
    spawn_menu_options(world, canvas, int2_zero, float2_half);
}

void button_event_menu_main(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // we should just check root ui -> trigger_entity
    const ecs_entity_t canvas = zox_get_value(trigger_entity, CanvasLink)
    find_child_with_tag(canvas, MenuOptions, found_child)
    if (found_child == 0) return; // failed to find ...
    zox_delete_and_set(found_child)
    spawn_main_menu(world, canvas, game_name, int2_zero, float2_half);
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
