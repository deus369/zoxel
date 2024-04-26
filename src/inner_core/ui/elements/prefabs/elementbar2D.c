ecs_entity_t prefab_elementbar2D;
ecs_entity_t prefab_elementbar2D_front;

ecs_entity_t spawn_prefab_elementbar2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_elementbar2D")
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, { back_bar_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    prefab_elementbar2D = e;
    return e;
}

ecs_entity_t spawn_prefab_elementbar2D_front(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_bar_front2D")
    add_ui_plus_components(world, e);
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, { front_bar_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    // zox_prefab_set(e, GenerateTexture, { 1 })
    prefab_elementbar2D_front = e;
    return e;
}

ecs_entity_t spawn_elementbar2D_front(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const unsigned char layer, const int2 canvas_size, const unsigned char render_disabled) {
    const int2 pixel_size = (int2) { 0, parent_pixel_size.y };
    const float2 anchor = float2_half;
    const int2 pixel_position_global = parent_pixel_position_global;
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_elementbar2D_front)
    zox_name("elementbar2D_front")
    initialize_element(world, e, parent, canvas, int2_zero, pixel_size, int2_one, anchor, layer, position2D, pixel_position_global);
    zox_set(e, RenderDisabled, { render_disabled })
    return e;
}

ecs_entity_t spawn_elementbar2D(ecs_world_t *world, const ecs_entity_t ui_holder, const ecs_entity_t canvas, const ecs_entity_t parent, int2 pixel_position, const int2 padding, const float2 anchor, const char* text, const int font_size, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size, const unsigned char render_disabled) {
    const unsigned char front_bar_layer = layer + 1;
    const unsigned char zext_layer = layer + 2;
    const int2 zext_size = (int2) { font_size * strlen(text), font_size };
    const int2 pixel_size = (int2) { font_size * 16 + padding.x * 2, zext_size.y + padding.y * 2 };
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_elementbar2D)
    zox_name("elementbar2D")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, int2_one, anchor, layer, position2D, pixel_position_global);
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, Color, { back_bar_color })
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 2)
    children->value[0] = spawn_elementbar2D_front(world, canvas, e, pixel_position_global, pixel_size, front_bar_layer, canvas_size, render_disabled);
    children->value[1] = spawn_zext(world, prefab_zext, e, canvas, int2_zero, float2_half, int2_to_byte2(padding), text, font_size, 0, zext_layer, pixel_position_global, zext_size, render_disabled);
    zox_modified(e, Children)
    return e;
}

/*zox_log("   > pixel_size [%ix%i]\n", pixel_size.x, pixel_size.y)
zox_log("   > pixel_position [%ix%i]\n", pixel_position.x, pixel_position   .y)
zox_log("   > pixel_position_global [%ix%i]\n", pixel_position_global.x, pixel_position_global.y)*/
