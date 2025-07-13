ecs_entity_t spawn_prefab_element_textured(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_element_textured")

    // frame texture
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, Seed, { 666 })
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger })
    zox_prefab_set(e, FrameCorner, { default_button_corner })
    zox_prefab_set(e, OutlineThickness, { default_button_frame_thickness })
    zox_prefab_set(e, Color, { default_fill_color })
    zox_prefab_set(e, OutlineColor, { default_outline_color })

    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, ElementSpawn *data) {
    int2 position = data->element.position;
    data->element.position_in_canvas = get_element_pixel_position_global(data->parent.position, data->parent.size, position, data->element.anchor);
    const float2 real_position = get_element_position(data->element.position_in_canvas, data->canvas.size);
    anchor_element_position2D(&position, data->element.anchor, data->element.size);
    zox_instance(data->element.prefab)
    zox_name("element")
    initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, data->element.position_in_canvas);
    zox_set(e, Color, { data->texture.fill_color })
    zox_set(e, OutlineColor, { data->texture.outline_color })
    return e;
}

ecs_entity_t spawn_element_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    ElementSpawn spawn_element_data = {
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
            .prefab = prefab_element_textured,
            .layer = 2,
            .anchor = anchor,
            .position = pixel_position,
            .size = pixel_size
        },
        .texture = {
            .fill_color = default_fill_color,
            .outline_color = default_outline_color,
        }
    };
    return spawn_element(world, &spawn_element_data);
}