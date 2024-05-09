ecs_entity_t spawn_prefab_elementbar3D_front(ecs_world_t *world) {
    zox_prefab_child(prefab_element_world_child)
    zox_prefab_name("prefab_elementbar3D_front")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, { front_bar_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_front_mesh_scale);
    prefab_elementbar3D_front = e;
    return e;
}

// used atm for statbar front bar
ecs_entity_t spawn_elementbar3D_front(ecs_world_t *world, const ecs_entity_t ui_holder, const ecs_entity_t parent, const float3 offset) {
    const ecs_entity_t lookat_camera = main_cameras[0];
    const ecs_entity_t canvas = main_canvas; //  zox_get_value(ui_holder, CanvasLink)
    zox_instance(prefab_elementbar3D_front)
    zox_name("elementbar3D_front")
    zox_set(e, CameraLink, { lookat_camera })
    zox_set(e, CanvasLink, { canvas })
    zox_set(e, ParentLink, { parent })
    zox_set(e, LocalPosition3D, { offset })
    return e;
}
