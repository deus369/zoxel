ecs_entity_t element_prefab;

ecs_entity_t spawn_prefab_element(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    zoxel_add_tag(world, e, FrameTexture);
    zoxel_set(world, e, Color, {{ 66, 35, 25, 255 }});
    zoxel_set(world, e, SelectableState, { 0 });
    add_ui_plus_components(world, e);
    // zoxel_add_tag(world, e, SaveTexture);
    ecs_defer_end(world);
    element_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab element [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, element_prefab);
    initialize_ui_components(world, e, parent, position, size, anchor, 0, canvas_size);
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned element [%lu]\n", (long int) e);
    #endif
    return e;
}