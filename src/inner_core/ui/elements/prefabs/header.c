extern void button_event_close_window(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element);

ecs_entity_t spawn_prefab_button_close(ecs_world_t *world) {
    zox_prefab_child(prefab_button)
    zox_prefab_name("prefab_header")
    zox_add_tag(e, CloseButton)
    zox_prefab_set(e, ClickEvent, { &button_event_close_window })
    prefab_close_button = e;
}

ecs_entity_t spawn_prefab_header(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_header")
    add_ui_plus_components(world, e);
    add_selectable_components(world, e);
    add_draggable_components(world, e);
    zox_add_tag(e, Header)
    zox_add_tag(e, FrameTexture)
    zox_add_tag(e, TextureAddNoise)
    zox_prefab_set(e, Color, { header_color })
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Children, { 0, NULL })
    header_prefab = e;
    return e;
}

ecs_entity_t spawn_close_button(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 parent_position, const int2 parent_size, const int2 position, const int size, byte2 padding, const unsigned char layer, const int2 canvas_size) {
    const float2 anchor = (float2) { 1, 0.5f };
    SpawnButton spawnButton = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = parent,
            .position = parent_position,
            .size = parent_size },
        .element = {
            .position = position,
            .layer = layer,
            .anchor = anchor },
        .zext = {
            .prefab = prefab_zext,
            .text = "X",
            .font_size = size,
            .padding = padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color },
        .button = {
            .prefab = prefab_close_button,
            .color = button_color }};
    const ecs_entity_t e = spawn_button(world, &spawnButton);
    return e;
}

ecs_entity_t spawn_header(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor, const char* text, const int font_size, int header_margins, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const unsigned char is_close_button, const int2 canvas_size) {
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
    const unsigned char zext_layer = layer + 1;
    const unsigned char button_layer = layer + 2;
    zox_instance(header_prefab)
    zox_name("header")
    zox_set(e, DraggedLink, { parent })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, global_position);
    Children *children = zox_get_mut(e, Children)
    SpawnZext zextSpawnData = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = e,
            .position = global_position,
            .size = pixel_size },
        .element = {
            .layer = zext_layer,
            .anchor = zext_anchor,
            .position = zext_position },
        .zext = {
            .prefab = prefab_zext,
            .text = text,
            .font_size = font_size,
            .padding = padding,
            .font_fill_color = header_font_fill_color,
            .font_outline_color = header_font_outline_color } };
    add_to_Children(children, spawn_zext(world, &zextSpawnData));
    if (is_close_button) {
        int2 close_button_position = (int2) { - (font_size / 2) - header_margins / 2, 0 };
        add_to_Children(children, spawn_close_button(world, e, canvas, global_position, pixel_size, close_button_position, font_size, padding, button_layer, canvas_size));
    }
    zox_modified(e, Children)
    return e;
}
