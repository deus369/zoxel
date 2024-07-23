ecs_entity_t spawn_prefab_zext(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zext")
    zox_add_tag(e, Zext)
    add_ui_plus_components_invisible(world, e);
    zox_prefab_set(e, ZextSize, { 0 })
    zox_prefab_set(e, ZextPadding, { byte2_zero })
    zox_prefab_set(e, ZextDirty, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, FontOutlineColor, { { 255, 0, 0, 255 }})
    zox_prefab_set(e, FontFillColor, { { 0, 255, 0, 255 }})
    zox_prefab_set(e, FontThickness, { 1 })
    zox_prefab_add(e, ZextData)
    zox_prefab_set(e, Children, { 0, NULL })
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, const SpawnZext *data) {
    const int2 element_canvas_position = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 position2D = get_element_position(element_canvas_position, data->canvas.size);
    zox_instance(data->element.prefab)
    zox_name("zext")
    zox_set(e, RenderDisabled, { data->element.render_disabled })
    zox_set(e, ZextSize, { data->zext.font_size })
    zox_set(e, ZextPadding, { data->zext.padding })
    zox_set(e, MeshAlignment, { data->zext.alignment })
    zox_set(e, FontFillColor, { data->zext.font_fill_color })
    zox_set(e, FontOutlineColor, { data->zext.font_outline_color })
    zox_set(e, FontThickness, { data->zext.font_thickness })
    zox_get_muter(e, ZextData, zextData)
    zox_get_muter(e, Children, children)
    const int zext_data_length = data->zext.text != NULL ? strlen(data->zext.text) : 0;
    initialize_memory_component(ZextData, zextData, unsigned char, zext_data_length)
    for (int i = 0; i < zextData->length; i++) zextData->value[i] = convert_ascii(data->zext.text[i]);
    const int zigels_count = calculate_total_zigels(zextData->value, zextData->length);
    initialize_memory_component(Children, children, ecs_entity_t, zigels_count)
    const int2 pixel_size = calculate_zext_size(zextData->value, zextData->length, data->zext.font_size, data->zext.padding, default_line_padding);
    SpawnZigel spawn_data = {
        .canvas = data->canvas,
        .parent = {
            .e = e,
            .position = element_canvas_position,
            .size = data->element.size
        },
        .zext = {
            .length = zigels_count,
            .text_padding = data->zext.padding,
            .text_alignment = data->zext.alignment,
            .font_thickness = data->zext.font_thickness
        },
        .element = {
            .layer = data->element.layer + 1,
            .size = int2_single(data->zext.font_size)
        },
        .zigel = {
            .outline_color = data->zext.font_outline_color,
            .fill_color = data->zext.font_fill_color,
        }
    };
    for (int i = 0; i < zigels_count; i++) {
        const int data_index = calculate_zigel_data_index(zextData->value, zextData->length, i);
        const unsigned char zigel_index = calculate_zigel_index(zextData->value, zextData->length, i);
        spawn_data.zigel.data_index = data_index;
        spawn_data.zigel.zigel_index = zigel_index;
        children->value[i] = spawn_zext_zigel(world, zextData, &spawn_data);
        zox_set(children->value[i], RenderDisabled, { data->element.render_disabled })
    }
    // this has to be done under as memory shifts a round with the points, when zox_set is called
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, pixel_size, pixel_size, data->element.anchor, data->element.layer, position2D, element_canvas_position);
    return e;
}
