ecs_entity_t prefab_label_background;

ecs_entity_t spawn_prefab_label_background(ecs_world_t *world) {
    zox_prefab_child(prefab_zext)
    zox_prefab_name("prefab_label_background")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Label)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 35, 88, 66, 255 }})
    prefab_label_background = e;
    return e;
}

ecs_entity_t spawn_label_background(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, float2 anchor, byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, int2 parent_pixel_position_global, int2 parent_pixel_size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 pixel_size = (int2) { font_size * sizeof(text) + padding.x * 2, font_size + padding.y * 2 };
    const float2 element_anchor = (float2) { 0.5f, anchor.y }; // because text rendering will reposition it, for now do this
    const float2 zext_anchor = anchor;
    anchor_element_position2D(&pixel_position, element_anchor, pixel_size);
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, element_anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    ecs_entity_t e = spawn_zext(world, prefab, parent, canvas, pixel_position, zext_anchor, padding, text, font_size, alignment, layer, parent_pixel_position_global, parent_pixel_size, 0);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, zext_anchor, layer, position2D, pixel_position_global);
    zox_name("label_background")
    return e;
}

/*zox_logg("   > canvas label\n")
zox_log("       > pixel_position [%ix%i]\n", pixel_position.x, pixel_position.y)
zox_log("       > pixel_size [%ix%i]\n", pixel_size.x, pixel_size.y)
zox_log("       > pixel_position_global [%ix%i]\n", pixel_position_global.x, pixel_position_global.y)
zox_log("       > position2D [%fx%f]\n", position2D.x, position2D.y)
zox_log("       > canvas_size [%ix%i]\n", canvas_size.x, canvas_size.y)*/
/*zox_log("   > label_background %lu\n", e)
zox_log("       > pix pos [%ix%i]\n", pixel_position.x, pixel_position.y)
zox_log("       > anchor [%fx%f]\n", anchor.x, anchor.y)
zox_log("       > pix pos global [%ix%i]\n", pixel_position_global.x, pixel_position_global.y)
zox_log("       > position2D [%fx%f]\n", position2D.x, position2D.y)*/
