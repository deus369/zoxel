// todo: remove any canvas elements, these will just be world transform uis
ecs_entity_t prefab_element_world;

ecs_entity_t spawn_prefab_element3D(ecs_world_t *world) {
    zox_prefab()
    zox_add_tag(e, Element3D)
    zox_add_tag(e, FillTexture)
    zox_add_tag(e, SingleMaterial)
    zox_add_tag(e, ElementBillboard)
    zox_set(e, CameraLink, { 0 })
    zox_set(e, UIHolderLink, { 0 })
    zox_set(e, UITrail, {{ 0, 0.33f, 0 }})
    // todo: add alpha to a texture3D shader variant
    // zox_set(e, Color, {{ 66, 12, 12, 0 }})
    zox_set(e, Color, {{ 0, 255, 0, 255 }}) 
    add_ui_components_world(world, e, (float2) { 0.2f, 0.05f });
    prefab_element_world = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawned prefab element_world [%lu].\n", (long int) (e));
    #endif
    return e;
}

// , ecs_entity_t camera, float3 offset
ecs_entity_t spawn_element3D(ecs_world_t *world, ecs_entity_t ui_holder) {
    int2 pixel_size = (int2) { 32, 8 };
    zox_instance(prefab_element_world)
    zox_set_only(e, UIHolderLink, { ui_holder })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}