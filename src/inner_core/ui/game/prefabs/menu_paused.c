ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_menu_paused")
    zox_add_tag(e, MenuPaused)
    prefab_menu_paused = e;
    return e;
}

ecs_entity_t spawn_menu_paused(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor, const unsigned char layer) {
    const int labels_count = 2;
    const unsigned char is_close_button = 0;
    const text_group labels[] = { { "return" }, { "leave" } };
    const ClickEvent events[] = { { &button_event_return_to_game }, { &button_event_end_game } };
    const ecs_entity_t e = spawn_ui_list(world, prefab_menu_paused, canvas, "paused", labels_count, labels_count, labels, events, position, anchor, is_close_button, 22, layer, 0, player);
    zox_name("menu_paused")
    return e;
}

ecs_entity_t spawn_menu_paused_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    return spawn_menu_paused(world, player, canvas, int2_zero, float2_half, pause_ui_overlay_layer + 3);
}
