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

ecs_entity_t spawn_zext(ecs_world_t *world, const ZextSpawnData *data) {
    const int zext_length = data->text != NULL ? strlen(data->text) : 0;
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
