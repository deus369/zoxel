ecs_entity_t spawn_prefab_elementbar3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_elementbar3D")
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { back_bar_color_3D_start })
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_add(e, Children)
    zox_set(e, UITrail, {{ 0, 0.43f, 0 }})
    return e;
}

ecs_entity_t spawn_elementbar3D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t ui_holder, const float percentage, const byte render_disabled, const float position_y) {
    const float depth_difference = 0.0012f; // 0.012f;
    zox_instance(prefab)
    zox_name("elementbar3D")
    zox_set(e, UIHolderLink, { ui_holder })
    zox_set(e, UITrail, {{ 0, position_y, 0 }})
    zox_set(e, ElementBar, { percentage })
    zox_set(e, ElementBarSize, { statbar_front_mesh_scale })
    zox_set(e, RenderDisabled, { render_disabled })
    Children *children = &((Children) { 0, NULL });
    add_to_Children(children, spawn_elementbar3D_front(world, prefab_elementbar3D_front, ui_holder, e, (float3) { 0, 0, depth_difference }, render_disabled));
    zox_set(e, Children, { children->length, children->value })
    return e;
}

// const ecs_entity_t camera = main_cameras[0];
// const ecs_entity_t canvas = zox_canvases[0];
// zox_set(e, CameraLink, { camera })
// zox_set(e, CanvasLink, { canvas })