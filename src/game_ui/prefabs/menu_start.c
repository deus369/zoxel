char *label_start = "S T A R T";

void menu_start_triggered(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, MenuStart, menu)
    if (!menu) {
        // zox_log("! failed to find MenuStart\n")
        return;
    }
    zox_delete(menu)
    spawn_main_menu(world, player, canvas, game_name, int2_zero, float2_half);
}

void button_event_menu_start(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t canvas = zox_get_value(event->clicker, CanvasLink)
    menu_start_triggered(world, event->clicker, canvas);
}

ecs_entity_t spawn_prefab_main_start(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_menu_start")
    zox_add_tag(e, MenuStart)
    return e;
}

ecs_entity_t spawn_main_start(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t player, const ecs_entity_t canvas, const char *header_label, const int2 position, const float2 anchor) {
    const byte is_close_button = 0;
    const byte layer = 3;
    const int labels_count = 1;
    const text_group labels[] = { { label_start } };
    const ClickEvent events[] = { { &button_event_menu_start } };
    const ecs_entity_t e = spawn_ui_list(world, prefab, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0, player);
    zox_name("main_start")
    return e;
}

/*labels_count = 2;
 * const text_group labels[] = { { label_new }, { label_options } };
 * const ClickEvent events[] = { { &button_event_new_game }, { &button_event_menu_options } };
 * e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0, player);*/
