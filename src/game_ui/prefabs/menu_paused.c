ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_menu_paused")
    zox_add_tag(e, MenuPaused)
    return e;
}

ecs_entity_t spawn_menu_paused(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor, const unsigned char layer) {
    const unsigned char font_size = 26; // 22
    const unsigned char is_close_button = 0;
#ifdef zox_disable_save_games
    const int labels_count = 2;
    const text_group labels[] = { { "return" }, { "leave" } };
    const ClickEvent events[] = { { &button_event_return_to_game }, { &button_event_end_game } };
#else
    const int labels_count = 3;
    const text_group labels[] = { { "return" }, { "save" }, { "leave" } };
    const ClickEvent events[] = { { &button_event_return_to_game }, { &button_event_save_game }, { &button_event_end_game } };
#endif
    const ecs_entity_t e = spawn_ui_list(world, prefab_menu_paused, canvas, "paused", labels_count, labels_count, labels, events, position, anchor, is_close_button, font_size, layer, 0, player);
    zox_name("menu_paused")
    return e;
}

ecs_entity_t spawn_menu_paused_player(ecs_world_t *world, const ecs_entity_t player) {
    const float2 anchor = float2_half;  // (float2) { 0, 1 };
    const int2 position = int2_zero;    // (int2) { 100, -100 };
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    return spawn_menu_paused(world, player, canvas, position, anchor, pause_ui_overlay_layer + 3);
}
