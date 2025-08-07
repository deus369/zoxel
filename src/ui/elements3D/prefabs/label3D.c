entity spawn_prefab_label3D(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("label3D")
    zox_add_tag(e, FillTexture)
    zox_set(e, UITrail, {{ 0, 0.23f, 0 }});
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { label3D_fill })
    zox_prefab_set(e, Children, { 0, NULL });
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_back_mesh_scale);
    return e;
}

entity spawn_label3D(
    ecs *world,
    const SpawnDataElement3D data,
    Text3DData text_data,
    Zigel3DData zigel_data
) {
    if (!text_data.prefab) {
        zox_log("invalid text_data prefab in spawn_label3D\n")
        return 0;
    }
    zox_instance(data.prefab)
    zox_name("label3D")
    if (data.ui_holder) {
        zox_set(e, UIHolderLink, { data.ui_holder })
        zox_set(e, UITrail, { { 0, data.trail_offset, 0 } })
    }
    zox_set(e, RenderDisabled, { data.render_disabled })
    if (!is_color_null(data.base_color)) {
        zox_set(e, Color, { data.base_color })
    }
    text_data.position = (float3) { 0, 0, element3D_depth_difference };
    zigel_data.position = text_data.position;
    text_data.parent = e;
    const entity text = spawn_text3D(world, text_data, zigel_data);
    Children *children = &((Children) { 0, NULL });
    add_to_Children(children, text);
    zox_set(e, Children, { children->length, children->value })
    return e;
}