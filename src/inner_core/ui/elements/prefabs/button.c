const color button_color = (color) { 43, 44, 53, 255 };
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

ecs_entity_t spawn_button(ecs_world_t *world, SpawnButton *data) {
    const int2 zext_size = (int2) { data->zext.font_size * strlen(data->zext.text), data->zext.font_size };
    const int2 pixel_size = (int2) { zext_size.x + data->zext.padding.x * 2, zext_size.y + data->zext.padding.y * 2 };
    const int2 global_position = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 position2D = get_element_position(global_position, data->canvas.size);
    zox_instance(data->button.prefab)
    zox_name("button")
    zox_set(e, Color, { data->button.color })
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, pixel_size, pixel_size, data->element.anchor, data->element.layer, position2D, global_position);
    if (data->element.render_disabled) zox_set(e, RenderDisabled, { data->element.render_disabled })
    SpawnZext spawnZext = {
        .canvas = data->canvas,
        .parent = {
            .e = e,
            .position = global_position,
            .size = pixel_size },
        .element = {
            .layer = data->element.layer + 1,
            .anchor = float2_half,
            .size = zext_size,
            .render_disabled = data->element.render_disabled, },
        .zext = data->zext };
    const ecs_entity_t zext = spawn_zext(world, &spawnZext);
    Children *children = zox_get_mut(e, Children)
    add_to_Children(children, zext);
    zox_modified(e, Children)
    return e;
}

ecs_entity_t spawn_button_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, int2 pixel_position, const byte2 padding, const color color, const char* text, int font_size, const float2 anchor, const ClickEvent event) {
    const ecs_entity_t parent = canvas;
    const unsigned char layer = 6;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    fix_text_for_screen_size(&pixel_position, &font_size, canvas_size);
    const int2 zext_size = (int2) { font_size * strlen(text), font_size };
    const int2 pixel_size = (int2) { zext_size.x + padding.x * 2, zext_size.y + padding.y * 2 };
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_button)
    zox_name("button_on_canvas")
    zox_set(e, Color, { color })
    zox_set(e, ClickEvent, { event.value })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    SpawnZext spawnZext = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = e,
            .position = pixel_position_global,
            .size = pixel_size },
        .element = {
            .layer = layer + 1,
            .anchor = float2_half,
            .size = zext_size },
        .zext = {
            .prefab = prefab_zext,
            .text = text,
            .font_size = font_size,
            .padding = padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color } };
    const ecs_entity_t zext = spawn_zext(world, &spawnZext);
    Children *children = zox_get_mut(e, Children)
    add_to_Children(children, zext);
    zox_modified(e, Children)
    return e;
}


ecs_entity_t spawn_button_old(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const byte2 padding, const float2 anchor, const char* text, const int font_size, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size, const unsigned char render_disabled, const color button_color) {
    const int2 zext_size = (int2) { font_size * strlen(text), font_size };
    const int2 pixel_size = (int2) { zext_size.x + padding.x * 2, zext_size.y + padding.y * 2 };
    const int2 global_position = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(global_position, canvas_size);
    zox_instance(prefab_button)
    zox_name("button")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, global_position);
    zox_set(e, Color, { button_color })
    zox_set(e, RenderDisabled, { render_disabled })
    SpawnZext spawnZext = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = e,
            .position = global_position,
            .size = pixel_size },
        .element = {
            .layer = layer + 1,
            .anchor = float2_half,
            .size = zext_size,
            .render_disabled = render_disabled, },
        .zext = {
            .prefab = prefab_zext,
            .text = text,
            .font_size = font_size,
            .padding = padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color } };
    const ecs_entity_t zext = spawn_zext(world, &spawnZext);
    Children *children = zox_get_mut(e, Children)
    add_to_Children(children, zext);
    zox_modified(e, Children)
    return e;
}
