ecs_entity_t spawn_prefab_label3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_label3D")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_add(e, Children)
    zox_set(e, UITrail, {{ 0, 0.43f, 0 }})
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_back_mesh_scale);
    zox_prefab_set(e, Color, { color_black })
    return e;
}

ecs_entity_t spawn_label3D(ecs_world_t *world, const SpawnDataElement3D data, Text3DData text_data, Zigel3DData zigel_data) {
    if (!text_data.prefab) {
        zox_log("invalid text_data prefab in spawn_label3D\n")
        return 0;
    }
    zox_instance(data.prefab)
    zox_name("label3D")
    zox_set(e, UIHolderLink, { data.ui_holder })
    zox_set(e, UITrail, { { 0, data.position_y, 0 } })
    zox_set(e, RenderDisabled, { data.render_disabled })
    zox_set(e, Color, { data.base_color })
    Children *children = &((Children) { 0, NULL });
    text_data.position = (float3) { 0, 0, element3D_depth_difference * 2 };
    zigel_data.position = text_data.position;
    text_data.parent = e;
    const ecs_entity_t text = spawn_text3D(world, text_data, zigel_data);
    add_to_Children(children, text);
    zox_set(e, Children, { children->length, children->value })
    return e;
}