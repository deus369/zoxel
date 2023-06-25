ecs_entity_t prefab_element_world;
// todo: remove any canvas elements, these will just be world transform uis

ecs_entity_t spawn_prefab_element_world(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_element)
    zox_set(e, Color, {{ 125, 125, 125, 255 }})
    zox_set(e, CameraLink, { 0 })
    zox_set(e, UIHolderLink, { 0 })
    zox_set(e, UITrail, {{ 0, 2, 0 }})
    ecs_defer_end(world);
    prefab_element_world = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawned prefab element_world [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_element_world(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    ecs_defer_begin(world);
    zox_instance(prefab_element_world)
    initialize_ui_components(world, e, parent, position, size, anchor, 0, canvas_size);
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}