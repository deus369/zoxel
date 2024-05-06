ecs_entity_t prefab_zext;

ecs_entity_t spawn_prefab_zext(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zext")
    add_ui_plus_components_invisible(world, e);
    zox_add_tag(e, Zext)
    zox_prefab_set(e, ZextSize, { 0 })
    zox_prefab_set(e, ZextPadding, { byte2_zero })
    zox_prefab_set(e, ZextDirty, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, ZextData, { 0, NULL })
    zox_prefab_set(e, Children, { 0, NULL })
    zox_prefab_set(e, FontOutlineColor, { { 255, 0, 0, 255 }})
    zox_prefab_set(e, FontFillColor, { { 0, 255, 0, 255 }})
    prefab_zext = e;
    return e;
}

ecs_entity_t spawn_zext2(ecs_world_t *world, const ZextSpawnData *data) {
    const int2 canvas_size = zox_get_value(data->canvas.e, PixelSize)
    const int zext_length = strlen(data->text);
    const int2 pixel_size = (int2) { data->font_size * zext_length, data->font_size };
    const int2 element_canvas_position = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 position2D = get_element_position(element_canvas_position, data->canvas.size);
    zox_instance(data->prefab)
    zox_name("zext")
    zox_set(e, RenderDisabled, { data->element.render_disabled })
    zox_set(e, ZextSize, { data->font_size })
    zox_set(e, ZextPadding, { data->padding })
    zox_set(e, MeshAlignment, { data->alignment })
    zox_prefab_set(e, FontFillColor, { data->font_fill_color })
    zox_prefab_set(e, FontOutlineColor, { data->font_outline_color })
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, pixel_size, pixel_size, data->element.anchor, data->element.layer, position2D, element_canvas_position);
    ZextData *zextData = zox_get_mut(e, ZextData)
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(ZextData, zextData, unsigned char, zext_length)
    resize_memory_component(Children, children, ecs_entity_t, zext_length)
    ZigelSpawnData spawn_data = {
        .canvas = data->canvas,
        .parent = { .e = e, .position = element_canvas_position, .size = data->element.size },
        .zext = { .length = zext_length, .text_padding = data->padding, .text_alignment = data->alignment },
        .layer = data->element.layer + 1,
        .size = (int2) { data->font_size, data->font_size },
        .outline_color = data->font_outline_color,
        .fill_color = data->font_fill_color,
    };
    for (int i = 0; i < zext_length; i++) {
        spawn_data.array_index = i;
        spawn_data.zigel_index = convert_ascii(data->text[i]);
        zextData->value[i] = spawn_data.zigel_index;
        children->value[i] = spawn_zext_zigel(world, &spawn_data);
        zox_set(children->value[i], RenderDisabled, { data->element.render_disabled })
    }
    zox_modified(e, ZextData)
    zox_modified(e, Children)
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t parent, const ecs_entity_t canvas_entity, const int2 pixel_position, const float2 anchor, const byte2 text_padding, const char* text, const int font_size, unsigned char text_alignment, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_size, const unsigned char render_disabled) {
    const color font_outline_color = default_font_outline_color;
    const color font_fill_color = default_font_fill_color;
    const int2 canvas_size = zox_get_value(canvas_entity, PixelSize)
    const int zext_length = strlen(text);
    const unsigned char zigel_layer = layer + 1;
    const int2 pixel_size = (int2) { font_size * zext_length, font_size };
    const int2 element_canvas_position = get_element_pixel_position_global(parent_pixel_position_global, parent_size, pixel_position, anchor);
    const float2 position2D = get_element_position(element_canvas_position, canvas_size);
    zox_instance(prefab)
    zox_name("zext")
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, ZextSize, { font_size })
    zox_set(e, ZextPadding, { text_padding })
    zox_set(e, MeshAlignment, { text_alignment })
    zox_set(e, FontFillColor, { font_fill_color })
    zox_set(e, FontOutlineColor, { font_outline_color })
    initialize_element(world, e, parent, canvas_entity, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, element_canvas_position);
    ZextData *zextData = zox_get_mut(e, ZextData)
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(ZextData, zextData, unsigned char, zext_length)
    resize_memory_component(Children, children, ecs_entity_t, zext_length)
    ZigelSpawnData spawn_data = {
        .canvas = { .e = canvas_entity, .size = canvas_size },
        .parent = { .e = e, .position = element_canvas_position, .size = pixel_size },
        .zext = { .length = zext_length, .text_padding = text_padding, .text_alignment = text_alignment },
        .layer = zigel_layer,
        .size = (int2) { font_size, font_size },
        .fill_color = font_fill_color,
        .outline_color = font_outline_color,
    };
    for (int i = 0; i < zext_length; i++) {
        spawn_data.array_index = i;
        spawn_data.zigel_index = convert_ascii(text[i]);
        zextData->value[i] = spawn_data.zigel_index;
        children->value[i] = spawn_zext_zigel(world, &spawn_data);
        zox_set(children->value[i], RenderDisabled, { render_disabled })
    }
    zox_modified(e, ZextData)
    zox_modified(e, Children)
    return e;
}
