ecs_entity_t spawn_prefab_hierarchy(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("hierarchy")
    zox_add_tag(e, EditorElement)
    zox_add_tag(e, HierarchyUI)
    zox_prefab_set(e, HierarchyUIDirty, { 1 })
    return e;
}

// why does raycasting mess up after this spawns
ecs_entity_t spawn_editor_hierarchy(ecs_world_t *world, const ecs_entity_t canvas) {
    const int max_elements = 8;
    const byte is_scrollbar = 1;
    const ecs_entity_t player = 0; // zox_players[0];
    const char *header_label = "hierarchy";
    const byte ui_layer = 8;
    const byte is_close_button = 1;
    const int font_size = default_font_size;
    const int header_font_size = default_font_size + 4;
    const int labels_count = 0;
    const float2 anchor = (float2) { 0, 0.5f };
    const int2 position = int2_zero;
    const ecs_entity_t e = spawn_ui_list(world,
        prefab_hierarchy,
        canvas,
        header_label,
        labels_count,
        max_elements,
        NULL,
        NULL,
        NULL,
        NULL,
        position,
        anchor,
        is_close_button,
        header_font_size,
        font_size,
        ui_layer,
        is_scrollbar,
        player);
    zox_name("hierarchy")
    hierarchy = e;
    return e;
}