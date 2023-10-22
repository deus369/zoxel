// todo:
//  > spawn entities from a query
//  > selection on list ui
//  > multi selection on list ui
//  > click event linked to inspector ui of entity

ecs_entity_t prefab_hierarchy;
ecs_entity_t hierarchy;

ecs_entity_t spawn_prefab_hierarchy(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_hierarchy")
    zox_add_tag(e, EditorUI)
    zox_add_tag(e, HierarchyUI)
    zox_prefab_set(e, HierarchyUIDirty, { 1 })
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
    const int labels_count = 0;
    text_group labels[labels_count];
    ClickEvent events[labels_count];
    /*for (int i = 0; i < labels_count; i++) {
        // labels[i].text = "entity [0]";
        unsigned char *text = malloc(line_txt_length);
        snprintf(text, line_txt_length, "entity [%i]", i);
        labels[i].text = text;
        events[i].value = NULL;
        // zox_logg(text)
    }*/
    ecs_entity_t e = spawn_ui_list(world, prefab_hierarchy, canvas, header_label, labels_count, labels, events, int2_zero, float2_half, is_close_button, font_size, ui_layer);
    // for (int i = 0; i < labels_count; i++) free(labels[i].text);
    // spawn scrollbar too

    hierarchy = e;
    return e;
}
