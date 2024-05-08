ecs_entity_t prefab_elementbar3D;

ecs_entity_t spawn_prefab_elementbar3D(ecs_world_t *world) {
    zox_prefab_child(prefab_element_world)
    zox_prefab_name("prefab_elementbar3D")
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { back_bar_color_3D_start })
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_set(e, Children, { 0, NULL })
    prefab_elementbar3D = e;
    return e;
}

ecs_entity_t spawn_elementbar3D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t ui_holder, const float percentage) {
    const ecs_entity_t camera = main_cameras[0];
    const ecs_entity_t canvas = zox_canvases[0];
    const float depth_difference = 0.0012f; // 0.012f;
    zox_instance(prefab)
    zox_name("elementbar_3D")
    zox_set(e, UIHolderLink, { ui_holder })
    zox_set(e, CameraLink, { camera })
    zox_set(e, CanvasLink, { canvas })
    zox_set(e, ElementBar, { percentage })
    zox_set(e, ElementBarSize, { statbar_front_mesh_scale })
    Children *children = ecs_get_mut(world, e, Children);
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_elementbar3D_front(world, ui_holder, e, (float3) { 0, 0, depth_difference });
    zox_modified(e, Children)
    return e;
}
