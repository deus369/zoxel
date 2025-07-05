ecs_entity_t spawn_prefab_elementbar3D_front(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_elementbar3D_front")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, { front_bar3D_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    // prefab_set_mesh3D_vertices(world, e, square_vertices, 4, mesh_scale);
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_front_mesh_scale);
    return e;
}

// used atm for statbar front bar
ecs_entity_t spawn_elementbar3D_front(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t ui_holder, const ecs_entity_t parent, const float3 offset, const byte render_disabled) {
    zox_instance(prefab)
    zox_name("elementbar3D_front")
    zox_set(e, ParentLink, { parent })
    zox_set(e, LocalPosition3D, { offset })
    zox_set(e, RenderDisabled, { render_disabled })
    return e;
}