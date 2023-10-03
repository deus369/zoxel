ecs_entity_t prefab_element;

ecs_entity_t spawn_prefab_element(ecs_world_t *world) {
    zox_prefab()
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_prefab_set(e, SelectState, { 0 })
    add_ui_plus_components(world, e);
    prefab_element = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" > spawned prefab element [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    zox_instance(prefab_element)
    initialize_ui_components(world, e, parent, position, size, anchor, 0, canvas_size);
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned element [%lu]\n", e)
    #endif
    return e;
}

// zox_add_tag(e, SaveTexture)