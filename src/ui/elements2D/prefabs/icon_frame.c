// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_icon_frame(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame")
    zox_add_tag(e, IconFrame)
    zox_set(e, Color, { default_fill_color_frame })
    zox_set(e, OutlineColor, { default_outline_color_frame })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_3 spawn_icon_frame(ecs_world_t *world, SpawnIconFrame *data) {
    int2 position = data->element.position; // anchor our position
    const int2 position_in_canvas = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 real_position = get_element_position(position_in_canvas, data->canvas.size);
    anchor_element_position2D(&position, data->element.anchor, data->element.size);
    zox_instance(data->element.prefab)
    // zox_name("icon_frame")
    initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, position_in_canvas);
    zox_set(e, Color, { data->texture.fill_color })
    zox_set(e, OutlineColor, { data->texture.outline_color })
    SpawnIcon spawnIcon = {
        .canvas = data->canvas,
        .parent = {
            .e = e,
            .position = position_in_canvas,
            .size = data->element.size
        },
        .element = {
            .prefab = data->icon.prefab,
            .size = int2_single(data->icon.size),
            .anchor = float2_half,
            .layer = data->element.layer + 1,
        },
        .texture = data->icon.texture,
        .index = data->icon.index,
        .texture_size = data->icon.texture_size
    };
    Children *children = &((Children) { 0, NULL });
    const ecs_entity_t icon = spawn_icon(world, &spawnIcon);
    add_to_Children(children, icon);
    ecs_entity_t zext = 0;
    if (zox_has(data->element.prefab, IconLabel)) {
        const int font_size = 12;
        SpawnZext spawnZext = {
            .canvas = data->canvas,
            .parent = {
                .e = e,
                .position = position_in_canvas,
                .size = spawnIcon.element.size
            },
            .element = {
                .prefab = prefab_zext,
                .position = (int2) { -font_size - 4, font_size - 4 },
                .layer = data->element.layer + 2,
                .anchor = (float2) { 1, 0 },
                .size = spawnIcon.element.size,
                .render_disabled = data->element.render_disabled,
            },
            .zext = {
                .text = "",
                .font_size = font_size,
                .font_thickness = 2,
                // .padding = padding,
                .font_fill_color = default_font_fill_color,
                .font_outline_color = default_font_outline_color
            }
        };
        zext = spawn_zext(world, &spawnZext);
        add_to_Children(children, zext);
        zox_set_unique_name(zext, "icon_text")
    }
    zox_set(e, Children, { children->length, children->value })
    return (ecs_entity_3) { e, icon, zext };
}
