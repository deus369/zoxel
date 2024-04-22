ecs_entity_t prefab_hierarchy;
ecs_entity_t hierarchy = 0;

ecs_entity_t spawn_prefab_hierarchy(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_hierarchy")
    zox_add_tag(e, EditorElement)
    zox_add_tag(e, HierarchyUI)
    zox_prefab_set(e, HierarchyUIDirty, { 1 })
    prefab_hierarchy = e;
    return e;
}

// why does raycasting mess up after this spawns
ecs_entity_t spawn_editor_hierarchy(ecs_world_t *world, ecs_entity_t canvas) {
    const char *header_label = "hierarchy";
    const unsigned char ui_layer = 8;
    const unsigned char is_close_button = 1;
    const int font_size = 18;
    const int labels_count = 0;
    const int max_elements = 8;
    const float2 anchor = (float2) { 0, 0.5f };
    // const float2 anchor = float2_half;
    const int2 position = int2_zero;
    ecs_entity_t e = spawn_ui_list(world, prefab_hierarchy, canvas, header_label, labels_count, max_elements, NULL, NULL, position, anchor, is_close_button, font_size, ui_layer, 1);
    zox_name("hierarchy")
    hierarchy = e;
    return e;
}
