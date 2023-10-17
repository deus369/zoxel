ecs_entity_t prefab_hierarchy;
ecs_entity_t hierarchy;

ecs_entity_t spawn_prefab_hierarchy(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_hierarchy")
    zox_add_tag(e, EditorUI)
    prefab_hierarchy = e;
    return e;
}

// why does raycasting mess up after this spawns
ecs_entity_t spawn_editor_hierarchy(ecs_world_t *world, ecs_entity_t canvas) {
    int line_txt_length = 16;
    const char *header_label = "hierarchy";
    const unsigned char ui_layer = 8;
    const unsigned char is_close_button = 1;
    const int font_size = 18;
    const int labels_count = 4;
    text_group labels[labels_count];
    ClickEvent events[labels_count];
    for (int i = 0; i < labels_count; i++) {
        // labels[i].text = "entity [0]";
        unsigned char *text = malloc(line_txt_length);
        snprintf(text, line_txt_length, "entity [%i]", i);
        labels[i].text = text;
        events[i].value = NULL;
        // zox_logg(text)
    }
    ecs_entity_t e = spawn_ui_list(world, prefab_hierarchy, canvas, header_label, labels_count, labels, events, int2_zero, float2_half, is_close_button, font_size, ui_layer);
    for (int i = 0; i < labels_count; i++) free(labels[i].text);


    /*const int labels_count = 4;
    const text_group labels[] = { { "a" }, { "b" }, { "c" }, { "d" } };
    const ClickEvent events[] = { { NULL }, { NULL }, { NULL }, { NULL } };
    ecs_entity_t e = spawn_ui_list(world, prefab_hierarchy, main_canvas, header_label, labels_count, labels, events, int2_zero, float2_half, is_close_button, font_size, ui_layer);*/

    hierarchy = e;
    return e;
}
