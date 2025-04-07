typedef struct {
    float percentage;
    ecs_entity_t ui_holder;
    float position_y;
    Element3DData backbar;
    Element3DData frontbar;
} SpawnDataElementbar3D;

ecs_entity_t spawn_prefab_elementbar3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_elementbar3D")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, Color, { back_bar_color }) // back_bar_color_3D_start })
    zox_prefab_add(e, Children)
    zox_set(e, UITrail, {{ 0, 0.43f, 0 }})
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_back_mesh_scale);
    return e;
}

ecs_entity_2 spawn_elementbar3D(ecs_world_t *world, SpawnDataElementbar3D *data, Text3DData text_data, Zigel3DData zigel_data) {
    ecs_entity_2 output = { 0, 0 };
    zox_instance(data->backbar.prefab)
    output.x = e;
    zox_name("elementbar3D")
    zox_set(e, UIHolderLink, { data->ui_holder })
    zox_set(e, UITrail, { { 0, data->position_y, 0 } })
    zox_set(e, ElementBar, { data->percentage })
    zox_set(e, ElementBarSize, { statbar_front_mesh_scale })
    zox_set(e, RenderDisabled, { data->backbar.render_disabled })
    Children *children = &((Children) { 0, NULL });
    const float3 frontbar_position = (float3) { 0, 0, element3D_depth_difference };
    const ecs_entity_t frontbar = spawn_elementbar3D_front(world, data->frontbar.prefab, data->ui_holder, e, frontbar_position, data->frontbar.render_disabled);
    add_to_Children(children, frontbar);
    if (text_data.prefab) {
        text_data.position = (float3) { 0, 0, element3D_depth_difference * 2 };
        zigel_data.position = text_data.position;
        text_data.parent = e;
        const ecs_entity_t text = spawn_text3D(world, text_data, zigel_data);
        add_to_Children(children, text);
        output.y = text;
    }
    zox_set(e, Children, { children->length, children->value })
    return output;
}