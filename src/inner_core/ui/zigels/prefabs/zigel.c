ecs_entity_t prefab_zigel;
const int font_texture_mul = 2;

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
    const int2 texture_size = (int2) { pixel_size.x * font_texture_mul, pixel_size.y * font_texture_mul };
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, texture_size, anchor, layer, position, pixel_position_global);
    return e;
}
