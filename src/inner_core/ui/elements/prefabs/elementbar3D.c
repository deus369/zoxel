ecs_entity_t prefab_statbar3D;

int get_statbars_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Statbar));
}

ecs_entity_t spawn_prefab_elementbar3D(ecs_world_t *world) {
    zox_prefab_child(prefab_element_world)
    zox_prefab_name("prefab_statbar")
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { back_bar_color_3D_start })
    zox_add_tag(e, Statbar)
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_set(e, Children, { 0, NULL })
    prefab_statbar3D = e;
    return e;
}

ecs_entity_t spawn_elementbar3D(ecs_world_t *world, const ecs_entity_t ui_holder, const float percentage) {
    const float depth_difference = 0.0012f; // 0.012f;
    zox_instance(prefab_statbar3D)
    zox_name("statbar3D")
    zox_set(e, UIHolderLink, { ui_holder })
    zox_set(e, CameraLink, { main_cameras[0] })
    zox_set(e, CanvasLink, { main_canvas })
    zox_set(e, ElementBar, { percentage })
    zox_set(e, ElementBarSize, { statbar_front_mesh_scale })
    Children *children = ecs_get_mut(world, e, Children);
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_elementbar3D_front(world, ui_holder, e, (float3) { 0, 0, depth_difference });
    zox_modified(e, Children)
    return e;
}
