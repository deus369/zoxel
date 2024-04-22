ecs_entity_t prefab_element_world;

ecs_entity_t spawn_prefab_element3D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_world")
    zox_add_tag(e, Element3D)
    zox_add_tag(e, FillTexture)
    zox_add_tag(e, ElementBillboard)
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, UIHolderLink, { 0 })
    zox_prefab_set(e, UITrail, {{ 0, 0.33f, 0 }})
    zox_prefab_set(e, Color, {{ 0, 255, 0, 255 }}) 
    add_ui_components_world(world, e, (float2) { 0.2f, 0.05f });
    if (!headless) zox_add_tag(e, SingleMaterial)
    prefab_element_world = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawned prefab element_world [%lu]\n", e)
#endif
    return e;
}

// , ecs_entity_t camera, float3 offset
ecs_entity_t spawn_element3D(ecs_world_t *world, ecs_entity_t ui_holder) {
    int2 pixel_size = (int2) { 32, 8 };
    zox_instance(prefab_element_world)
    zox_prefab_name("element_world")
    zox_set(e, UIHolderLink, { ui_holder })
    zox_set(e, CameraLink, { main_cameras[0] })
    zox_set(e, CanvasLink, { main_canvas })
    zox_set(e, PixelSize, { pixel_size })
    zox_set(e, TextureSize, { pixel_size })
#ifdef zoxel_debug_spawns
    zox_log(" > spawned prefab element_world [%lu]\n", e)
#endif
    return e;
}
