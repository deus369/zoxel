ecs_entity_t label_background_prefab;

ecs_entity_t spawn_prefab_label_background(ecs_world_t *world) {
    zox_prefab_child(zext_prefab)
    zox_prefab_name("prefab_label_background")
    zox_add_tag(e, Label)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 35, 88, 66, 255 }})
    add_ui_plus_components(world, e);
    label_background_prefab = e;
    #ifdef zoxel_debug_prefabs
        zox_log("spawn_prefab label_background [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_label_background(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, float2 anchor, byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, int2 parent_pixel_position_global, int2 parent_pixel_size) {
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    int2 pixel_size = (int2) { font_size * sizeof(text) + padding.x * 2, font_size + padding.y * 2 };
    ecs_entity_t e = spawn_zext(world, prefab, parent, canvas, pixel_position, anchor, padding, text, font_size, alignment, layer, parent_pixel_position_global, parent_pixel_size, 0);
    zox_name("label_background")
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, pixel_size, anchor, layer, position2D, pixel_position_global);
    /*zox_log("   > label_background %lu\n", e)
    zox_log("       > pix pos [%ix%i]\n", pixel_position.x, pixel_position.y)
    zox_log("       > anchor [%fx%f]\n", anchor.x, anchor.y)
    zox_log("       > pix pos global [%ix%i]\n", pixel_position_global.x, pixel_position_global.y)
    zox_log("       > position2D [%fx%f]\n", position2D.x, position2D.y)*/
    return e;
}
