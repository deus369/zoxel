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
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab zigel [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, unsigned char index, int2 pixel_position, int2 size, float2 anchor, unsigned char layer, int2 parent_pixel_position_global, int2 parent_pixel_size, int2 canvas_size) {
    // color zigel_color = (color) { 55 + rand() % 60, 150 + rand() % 75, 135 + rand() % 70, 255 };
    color zigel_color = (color) { 22, 177, 133, 255 };
    zox_instance(prefab_zigel)
    zox_name("zigel")
    zox_set(e, ZigelIndex, { index })
    zox_set(e, Color, { zigel_color })
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position = get_element_position(pixel_position_global, canvas_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, size, anchor, layer, position, pixel_position_global);
#ifdef zoxel_debug_spawns
    zox_log("   > spawned zigel [%lu]\n", e)
#endif
    return e;
}

// spawns a text character in a place
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, ecs_entity_t zext, ecs_entity_t canvas, int layer, unsigned char index, int total_length, unsigned char zigel_index, int font_size, unsigned char text_alignment, byte2 text_padding, int2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    int2 zigel_size = (int2) { font_size, font_size };
    int2 position = get_zigel_position(index, total_length, font_size, text_alignment, text_padding);
    return spawn_zigel(world, zext, canvas, zigel_index, position, zigel_size, float2_half, layer, parent_position, parent_pixel_size, canvas_size);
}
