ecs_entity_t prefab_zigel;

ecs_entity_t spawn_zigel_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zigel")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Zigel)
    zox_add_tag(e, FontTexture)
    zox_prefab_set(e, ZigelIndex, { 0 })
    zox_prefab_set(e, Color, {{ 55, 185, 125, 255 }})
    prefab_zigel = e;
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t canvas, const unsigned char index, int2 pixel_position, const int2 pixel_size, const float2 anchor, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size) {
    // color zigel_color = (color) { 55 + rand() % 60, 150 + rand() % 75, 135 + rand() % 70, 255 };
    const color zigel_color = (color) { 22, 177, 133, 255 };
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_zigel)
    zox_name("zigel")
    zox_set(e, ZigelIndex, { index })
    zox_set(e, Color, { zigel_color })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position, pixel_position_global);
    return e;
}

// spawns a text character in a place
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, ecs_entity_t zext, const ecs_entity_t canvas, const int layer, const unsigned char index, const int total_length, const unsigned char zigel_index, const int font_size, const unsigned char text_alignment, const byte2 text_padding, const int2 parent_position, const int2 parent_pixel_size, const int2 canvas_size) {
    const int2 zigel_size = (int2) { font_size, font_size };
    const int2 position = get_zigel_position(index, total_length, font_size, text_alignment, text_padding);
    return spawn_zigel(world, zext, canvas, zigel_index, position, zigel_size, float2_half, layer, parent_position, parent_pixel_size, canvas_size);
}
