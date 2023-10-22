ecs_entity_t prefab_scrollbar;
ecs_entity_t prefab_scrollbar_front;

ecs_entity_t spawn_prefab_scrollbar(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_scrollbar")
    zox_add_tag(e, Scrollbar)
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    add_frame_texture_type(world, e, (color) { 35, 88, 66, 255 }, 7, 3);
    zox_prefab_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    prefab_scrollbar = e;
    #ifdef zoxel_debug_prefabs
        zox_log("   > spawn_prefab scrollbar [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_prefab_scrollbar_front(ecs_world_t *world) {
    zox_prefab_child(prefab_element)
    zox_prefab_name("prefab_scrollbar_front")
    zox_add_tag(e, Scrollbar)
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    add_draggable_components(world, e);
    zox_prefab_set(e, DraggableLimits, { int2_zero })
    prefab_scrollbar_front = e;
    #ifdef zoxel_debug_prefabs
        zox_log("   > spawn_prefab scrollbar_front [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_scrollbar_front(ecs_world_t *world, ecs_entity_t parent, int2 position, float2 anchor, unsigned char layer, int width, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    unsigned char zext_layer = layer + 1;
    int2 size = (int2) { width, width };
    zox_instance(prefab_scrollbar_front)
    zox_name("scrollbar_front")
    zox_set(e, DraggableLimits, { (int2) { 0, (parent_pixel_size.y / 2) - width / 2 } })
    float2 position2D = initialize_ui_components_2(world, e, parent, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned scrollbar_front [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_scrollbar(ecs_world_t *world, ecs_entity_t parent, int2 position, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, int width, int2 canvas_size) {
    unsigned char child_layer = layer + 1;
    float2 anchor = (float2) { 1.0f, 0.5f };
    int2 size = (int2) { width, parent_pixel_size.y };
    zox_instance(prefab_scrollbar)
    zox_name("scrollbar")
    float2 position2D = initialize_ui_components_2(world, e, parent, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    Children *children = zox_get_mut(e, Children);
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_scrollbar_front(world, e, int2_zero, float2_half, child_layer, width, position2D, size, canvas_size);
    zox_modified(e, Children)
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned scrollbar [%lu]\n", e)
    #endif
    return e;
}
