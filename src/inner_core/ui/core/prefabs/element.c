ecs_entity_t prefab_element;

ecs_entity_t spawn_prefab_element(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 7 })
    zox_set(e, OutlineThickness, { 3 })
    zox_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_set(e, SelectableState, { 0 })
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    prefab_element = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawned prefab element [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    // ecs_defer_begin(world);
    zox_instance(prefab_element)
    initialize_ui_components(world, e, parent, position, size, anchor, 0, canvas_size);
    // ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned element [%lu]\n", (long int) e);
    #endif
    return e;
}

// zox_add_tag(e, SaveTexture)