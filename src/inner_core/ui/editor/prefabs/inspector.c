ecs_entity_t prefab_inspector;
ecs_entity_t inspector;

ecs_entity_t spawn_prefab_inspector(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)    // prefab_window
    zox_prefab_name("prefab_inspector")
    zox_add_tag(e, MainMenu)
    prefab_inspector = e;
    return e;
}

ecs_entity_t spawn_inspector(ecs_world_t *world, ecs_entity_t canvas) {
    float2 anchor = { 0.5f, 0.5f };
    int2 position = int2_zero;
    const unsigned char layer = 8;
    const unsigned char is_close_button = 1;
    const int font_size = 24;
    int labels_count = 1;
    const text_group labels[] = { { "realm" } };
    const ClickEvent events[] = { { &button_event_play_game } };
    ecs_entity_t e = spawn_ui_list(world, prefab_inspector, canvas, "inspector", labels_count, labels_count, labels, events, position, anchor, is_close_button, font_size, layer);
    inspector = e;
    return e;
}
