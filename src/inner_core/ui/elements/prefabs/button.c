const color button_color = (color) {  22, 6, 8, 255 };
ecs_entity_t prefab_button;

ecs_entity_t spawn_prefab_button(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_button")
    add_ui_plus_components(world, e);
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    zox_add_tag(e, Button)
    zox_add_tag(e, ClickMakeSound)
    add_frame_texture_type(world, e, (color) { 35, 88, 66, 255 }, 7, 3);
    zox_prefab_set(e, Children, { 0, NULL })
    prefab_button = e;
    return e;
}

ecs_entity_t spawn_button(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const int2 padding, const float2 anchor, const char* text, const int font_size, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size, const unsigned char render_disabled) {
    const unsigned char zext_layer = layer + 1;
    const int2 zext_size = (int2) { font_size * strlen(text), font_size };
    const int2 pixel_size = (int2) { zext_size.x + padding.x * 2, zext_size.y + padding.y * 2 };
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_button)
    zox_name("button")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_set(e, Color, { button_color })
    zox_set(e, RenderDisabled, { render_disabled })
    const ecs_entity_t zext = spawn_zext(world, prefab_zext, e, canvas, int2_zero, float2_half, int2_to_byte2(padding), text, font_size, 0, zext_layer, pixel_position_global, zext_size, render_disabled);
    Children *children = zox_get_mut(e, Children)
    add_to_Children(children, zext);
    // resize_memory_component(Children, children, ecs_entity_t, 1)
    // children->value[0] = zext;
    zox_modified(e, Children)
    return e;
}

ecs_entity_t spawn_button_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, int2 pixel_position, const byte2 padding, const color color, const char* text, int font_size, const float2 anchor, const ClickEvent event) {
    ecs_entity_t parent = canvas;
    const unsigned char layer = 6;
    fix_text_for_screen_size(&pixel_position, &font_size, screen_dimensions);
    int2 zext_size = (int2) { font_size * strlen(text), font_size };
    int2 pixel_size = (int2) { zext_size.x + padding.x * 2, zext_size.y + padding.y * 2 };
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    zox_instance(prefab_button)
    zox_name("button_on_canvas")
    zox_set(e, Color, { color })
    zox_set(e, ClickEvent, { event.value })
    int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_zext(world, prefab_zext, e, canvas, (int2) { 0, 0 }, (float2) { 0.5f, 0.5f }, padding, text, font_size, 0, (layer + 1), pixel_position_global, zext_size, 0);
    zox_modified(e, Children)
    return e;
}

    /*zox_log("   > button %lu\n", e)
    zox_log("       > pix pos [%ix%i]\n", pixel_position.x, pixel_position.y)
    zox_log("       > anchor [%fx%f]\n", anchor.x, anchor.y)
    zox_log("       > pix pos global [%ix%i]\n", pixel_position_global.x, pixel_position_global.y)
    zox_log("       > position2D [%fx%f]\n", position2D.x, position2D.y)*/
