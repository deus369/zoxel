ecs_entity_t spawn_main_menu(ecs_world_t*, const ecs_entity_t, const ecs_entity_t, const char*);

void button_event_menu_main(ecs_world_t *world, const ClickEventData *event) {
    zox_geter_value(event->clicker, CanvasLink, ecs_entity_t, canvas)
    find_child_with_tag(canvas, MenuOptions, menu)
    if (menu == 0) {
        zox_log_error("options menu not found")
        return;
    }
    zox_delete(menu)
    spawn_main_menu(world, event->clicker, canvas, game_name);
}

void button_event_volume_increase(ecs_world_t *world, const ClickEventData *event) {
    if (master_volume < 1.0f) {
        master_volume += master_volume_increment;
        zox_log(" > increased the volume to [%f]", master_volume)
    }
}

void button_event_volume_decrease(ecs_world_t *world, const ClickEventData *event) {
    if (master_volume > 0) {
        master_volume -= master_volume_increment;
        zox_log(" > decreased the volume to [%f]", master_volume)
    }
}