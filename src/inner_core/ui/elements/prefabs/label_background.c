ecs_entity_t label_background_prefab;

ecs_entity_t spawn_prefab_label_background(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(zext_prefab)
    zox_name("prefab_label_background")
    zox_add_tag(e, Label)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 7 })
    zox_set(e, OutlineThickness, { 3 })
    zox_set(e, Color, {{ 35, 88, 66, 255 }})
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    label_background_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab label_background [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_label_background(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, int2 position, float2 anchor, byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    int2 size = (int2) { font_size * sizeof(text) + padding.x * 2, font_size + padding.y * 2 };
    ecs_entity_t e = spawn_zext(world, prefab, parent, position, anchor, padding, text, font_size, alignment, layer, parent_position2D, parent_pixel_size);
    zox_name("label_background")
    initialize_ui_components_2(world, e, parent, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    return e;
}