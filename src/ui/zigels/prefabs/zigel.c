ecs_entity_t spawn_zigel_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zigel")
    zox_add_tag(e, Zigel)
    zox_add_tag(e, FontTexture)
    add_ui_plus_components(world, e);
    zox_prefab_set(e, ZigelIndex, { 0 })
    zox_prefab_set(e, Color, { color_white })
    zox_prefab_set(e, SecondaryColor, { color_white })
    zox_prefab_set(e, FontThickness, { 1 })
    zox_prefab_set(e, FontOutlineThickness, { 2 })
    zox_prefab_set(e, TextureSize, { int2_single(4) })
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, const SpawnZigel *data) {
    const int2 texture_size = (int2) { data->element.size.x * 2, data->element.size.y * 2 };
    const int2 global_position = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 position = get_element_position(global_position, data->canvas.size);
    zox_instance(prefab_zigel)
    // zox_set_unique_name(e, "zigel")
    zox_name("zigel")
    zox_set(e, ZigelIndex, { data->zigel.zigel_index })
    zox_set(e, FontThickness, { data->zext.font_thickness })
    zox_set(e, Color, { data->zigel.fill_color })
    zox_set(e, SecondaryColor, { data->zigel.outline_color })
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, data->element.size, texture_size, data->element.anchor, data->element.layer, position, global_position);
    return e;
}
