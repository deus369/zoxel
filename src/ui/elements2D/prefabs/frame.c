// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_frame(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_frame")
    zox_add_tag(e, Frame)
    zox_prefab_add(e, Children)
    zox_prefab_set(e, Color, { default_fill_color_frame })
    zox_prefab_set(e, OutlineColor, { default_outline_color_frame })
    return e;
}

ecs_entity_3 spawn_frame(ecs_world_t *world, SpawnFrame *data) {
    zox_instance(data->element.prefab)
    zox_name("frame")
    set_element_spawn_data(world, e, data->canvas, data->parent, &data->element);
    zox_set(e, Color, { data->texture.fill_color })
    zox_set(e, OutlineColor, { data->texture.outline_color })
    CanvasSpawnData canvas_data = data->canvas;
    ParentSpawnData parent_data = {
        .e = e,
        .position = data->element.position_in_canvas,
        .size = data->element.size
    };
    SpawnIcon spawnIcon = {
        .canvas = canvas_data,
        .parent = parent_data,
        .element = {
            .prefab = data->icon.prefab,
            .layer = data->element.layer + 1,
            .size = int2_single(data->icon.size),
            .anchor = float2_half,
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
            .canvas = canvas_data,
            .parent = parent_data,
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

/*const int2 position_in_canvas = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
const float2 real_position = get_element_position(position_in_canvas, data->canvas.size);
// anchor our position
int2 position = data->element.position;
anchor_element_position2D(&position, data->element.anchor, data->element.size);
initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, position_in_canvas);*/
