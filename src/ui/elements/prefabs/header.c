ecs_entity_t spawn_prefab_header(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_header")
    zox_add_tag(e, Header)
    zox_add_tag(e, WindowRaycastTarget)
    zox_add_tag(e, TextureAddNoise)
    // set more details
    add_frame_texture_type(world, e, default_fill_color_header, default_outline_color_header, default_button_corner, default_button_frame_thickness);
    // add_ui_plus_components(world, e);
    add_selectable_components(world, e);
    add_draggable_components(world, e);
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_header(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor, const char* text, const int font_size, int header_margins, const byte layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const byte is_close_button, const int2 canvas_size) {
    const int string_length = strlen(text);
    int2 zext_position = (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!is_close_button) {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    const byte2 padding = (byte2) { (int) (font_size * 0.3f), (int) (font_size * 0.3f) };
    const int2 global_position = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(global_position, canvas_size);
    const byte zext_layer = layer + 1;
    const byte button_layer = layer + 2;
    zox_instance(prefab_header)
    zox_name("header")
    zox_set(e, DraggedLink, { parent })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, global_position);
    SpawnZext zextSpawnData = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = e,
            .position = global_position,
            .size = pixel_size },
        .element = {
            .prefab = prefab_zext,
            .layer = zext_layer,
            .anchor = zext_anchor,
            .position = zext_position },
        .zext = {
            .text = text,
            .font_size = font_size,
            .font_thickness = 4,
            .padding = padding,
            .font_fill_color = header_font_fill_color,
            .font_outline_color = header_font_outline_color
        }
    };
    zox_get_mutt(e, Children, children)
    const ecs_entity_t header_zext = spawn_zext(world, &zextSpawnData);
    add_to_Children(children, header_zext);
    if (is_close_button) {
        int2 close_button_position = (int2) { - (font_size / 2) - header_margins / 2, 0 };
        add_to_Children(children, spawn_close_button(world, e, canvas, global_position, pixel_size, close_button_position, font_size, padding, button_layer, canvas_size));
    }
    zox_modified(e, Children)
    return e;
}

ecs_entity_t spawn_header2(ecs_world_t *world, SpawnHeader *data) {
    const int string_length = strlen(data->zext.text);
    int2 zext_position = (int2) { ((data->zext.font_size * string_length) / 2) + data->header.margins, 0 };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!data->header.is_close_button) {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    const byte2 padding = (byte2) { (int) (data->zext.font_size * 0.3f), (int) (data->zext.font_size * 0.3f) };
    const int2 canvas_position = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 real_position = get_element_position(canvas_position, data->canvas.size);
    const byte zext_layer = data->element.layer + 1;
    const byte button_layer = data->element.layer + 2;
    zox_instance(data->element.prefab)
    zox_name("header")
    zox_set(e, DraggedLink, { data->parent.e })
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, canvas_position);
    SpawnZext zextSpawnData = {
        .canvas = data->canvas,
        .parent = {
            .e = e,
            .position = canvas_position,
            .size = data->element.size
        },
        .element = {
            .prefab = data->header.prefab_zext,
            .layer = zext_layer,
            .anchor = zext_anchor,
            .position = zext_position
        },
        .zext = data->zext
    };
    zox_get_mutt(e, Children, children)
    const ecs_entity_t header_zext = spawn_zext(world, &zextSpawnData);
    add_to_Children(children, header_zext);
    if (data->header.is_close_button) {
        const int2 close_button_position = (int2) { - (data->zext.font_size / 2) - data->header.margins, 0 };
        add_to_Children(children, spawn_close_button(world, e, data->canvas.e, canvas_position, data->element.size, close_button_position, data->zext.font_size, padding, button_layer, data->canvas.size));
    }
    zox_modified(e, Children)
    return e;
}
