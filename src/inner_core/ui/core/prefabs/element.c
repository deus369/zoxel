ecs_entity_t spawn_prefab_element(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element")
    add_ui_plus_components(world, e);
    add_frame_texture_type(world, e, color_white, 7, 3);
    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, SpawnElement *data) {
    int2 position = data->element.position;
    data->element.position_in_canvas = get_element_pixel_position_global(data->parent.position, data->parent.size, position, data->element.anchor);
    const float2 real_position = get_element_position(data->element.position_in_canvas, data->canvas.size);
    anchor_element_position2D(&position, data->element.anchor, data->element.size);
    zox_instance(data->prefab)
    zox_name("element")
    initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, data->element.position_in_canvas);
    zox_set(e, Color, { data->element.fill_color })
    // zox_log(" > element spawned [%ix%i]\n", data->element.size.x, data->element.size.y)
    return e;
}

ecs_entity_t spawn_element_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor) {
    const color random_color = (color) { 66, 35, 25, 255 };
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnElement spawn_element_data = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = canvas,
            .position = int2_half(canvas_size),
            .size = canvas_size
        },
        .element = {
            .layer = 2,
            .anchor = anchor,
            .position = pixel_position,
            .size = pixel_size,
            .fill_color = random_color
        },
        .prefab = prefab_element
    };
    return spawn_element(world, &spawn_element_data);
    // return spawn_element(world, prefab_element, canvas, canvas, pixel_position, pixel_size, anchor, 0, (color) { 66, 35, 25, 255 }, int2_half(canvas_size), canvas_size);
}


// obsolete, remove
/*ecs_entity_t spawn_element(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, int2 pixel_position, const int2 pixel_size, const float2 anchor, const unsigned char layer, const color element_color, const int2 parent_position, const int2 parent_size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, pixel_position, anchor);
    const float2 real_position = get_element_position(position_in_canvas, canvas_size);
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    zox_instance(prefab)
    zox_name("element")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, real_position, position_in_canvas);
    zox_set(e, Color, { element_color })
    return e;
}*/
