ecs_entity_t spawn_prefab_inspector(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)    // prefab_window
    zox_prefab_name("inspector")
    // zox_add_tag(e, Inspector)
    return e;
}

ecs_entity_t spawn_inspector(ecs_world_t *world, const ecs_entity_t canvas) {
    const int max_elements = 16;    // make this dynamic based on window size
    const ecs_entity_t player = 0; // zox_players[0];
    const byte layer = 12;
    const int font_size = default_font_size;
    const int header_font_size = default_font_size + 4;
    const float2 anchor = (float2) { 1, 0.5f };
    const int2 pixel_position = int2_zero;
    const byte is_scrollbar = 1;
    const byte is_close_button = 1;
    const int labels_count = 1; // 34;
    const text_group labels[] = { { "-------------------------------" } };
    const ecs_entity_t e = spawn_ui_list(world,
        prefab_inspector,
        canvas,
        "inspector",
        labels_count,
        max_elements,
        NULL,
        NULL,
        NULL,
        NULL,
        pixel_position,
        anchor,
        is_close_button,
        font_size,
        header_font_size,
        layer,
        is_scrollbar,
        player);
    zox_name("inspector")
    inspector = e;
    return e;
}

// const text_group labels[] = { { "[ ------ select entity ------ ]" } };
// const text_group labels[] = { { "[ select entity ]" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "[ ---------- -------------- ]" }  };
