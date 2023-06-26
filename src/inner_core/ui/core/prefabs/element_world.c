ecs_entity_t prefab_element_world;
// todo: remove any canvas elements, these will just be world transform uis

ecs_entity_t spawn_prefab_element_world(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, ElementBillboard)
    add_ui_components_world(world, e);
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 0 })
    zox_set(e, OutlineThickness, { 1 })
    zox_set(e, SelectableState, { 0 })
    zox_set(e, Color, {{ 125, 125, 125, 255 }})
    zox_add_tag(e, SingleMaterial)
    zox_set(e, CameraLink, { 0 })
    zox_set(e, UIHolderLink, { 0 })
    zox_set(e, UITrail, {{ 0, 0.33f, 0 }})
    ecs_defer_end(world);
    prefab_element_world = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawned prefab element_world [%lu].\n", (long int) (e));
    #endif
    return e;
}

// , ecs_entity_t camera, float3 offset
ecs_entity_t spawn_element_world(ecs_world_t *world, ecs_entity_t ui_holder) {
    int2 pixel_size = (int2) { 32, 8 }; // 8
    zox_instance(prefab_element_world)
    zox_set_only(e, UIHolderLink, { ui_holder })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    // initialize_ui_components(world, e, parent, position, size, anchor, 0, canvas_size);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}