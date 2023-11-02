ecs_entity_t prefab_inspector;
ecs_entity_t inspector;

ecs_entity_t spawn_prefab_inspector(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)    // prefab_window
    zox_prefab_name("prefab_inspector")
    // zox_add_tag(e, Inspector)
    prefab_inspector = e;
    return e;
}

ecs_entity_t spawn_inspector(ecs_world_t *world, ecs_entity_t canvas) {
    int2 position = int2_zero;
    const unsigned char layer = 12;
    const unsigned char is_close_button = 1;
    const int font_size = 18;
    int labels_count = 9;
    const text_group labels[] = { { "[ select entity ]" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "" }, { "[ ---------- -------------- ]" }  };
    // const ClickEvent events[] = { { NULL } };
    ecs_entity_t e = spawn_ui_list(world, prefab_inspector, canvas, "inspector", labels_count, labels_count, labels, NULL, position, float2_half, is_close_button, font_size, layer, 1);
    zox_name("inspector")
    inspector = e;
    return e;
}
