ecs_entity_t prefab_inspector;
ecs_entity_t inspector = 0;

ecs_entity_t spawn_prefab_inspector(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)    // prefab_window
    zox_prefab_name("prefab_inspector")
    // zox_add_tag(e, Inspector)
    prefab_inspector = e;
    return e;
}

ecs_entity_t spawn_inspector(ecs_world_t *world, ecs_entity_t canvas) {
    const unsigned char layer = 12;
    const unsigned char is_close_button = 1;
    const int font_size = 18;
    const int labels_count = 9;
    const text_group labels[] = { { "[ select entity ]" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "[ ---------- -------------- ]" }  };
    const float2 anchor = (float2) { 1, 0.5f };
    // const float2 anchor = float2_half;
    const int2 pixel_position = int2_zero;
    const int2 pixel_position_global = int2_zero;
    ecs_entity_t e = spawn_ui_list(world, prefab_inspector, canvas, "inspector", labels_count, labels_count, labels, NULL, pixel_position, anchor, is_close_button, font_size, layer, 1);
    zox_name("inspector")
    inspector = e;
    return e;
}
