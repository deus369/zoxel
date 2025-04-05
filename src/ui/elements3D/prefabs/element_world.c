ecs_entity_t spawn_prefab_element3D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element3D")
    zox_add_tag(e, Element3D)
    // zox_add_tag(e, FillTexture)
    zox_add_tag(e, ElementBillboard)
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, UIHolderLink, { 0 })
    zox_prefab_set(e, UITrail, {{ 0, 0.43f, 0 }})
    zox_prefab_set(e, Color, {{ 0, 255, 0, 255 }}) 
    add_ui_components_world(world, e, (float2) { 0.04f, 0.04f });
    if (!headless) zox_add_tag(e, SingleMaterial)
    return e;
}

// , ecs_entity_t camera, float3 offset
ecs_entity_t spawn_element3D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t ui_holder, const ecs_entity_t canvas) {
    // const ecs_entity_t camera = main_cameras[0]; // zox_get_value(ui_holder, CameraLink)
    const int2 pixel_size = (int2) { 32, 8 };
    zox_instance(prefab)
    zox_name("element3D")
    zox_set(e, UIHolderLink, { ui_holder })
    // zox_set(e, CameraLink, { camera })
    zox_set(e, CanvasLink, { canvas })
    zox_set(e, PixelSize, { pixel_size })
    zox_set(e, TextureSize, { pixel_size })
    return e;
}
