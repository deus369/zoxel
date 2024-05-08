ecs_entity_t prefab_zigel;

ecs_entity_t spawn_zigel_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zigel")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Zigel)
    zox_add_tag(e, FontTexture)
    zox_prefab_set(e, ZigelIndex, { 0 })
    zox_prefab_set(e, Color, { { 0, 0, 0, 255 }})
    zox_prefab_set(e, SecondaryColor, { { 0, 0, 0, 255 }})
    prefab_zigel = e;
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, const ZigelSpawnData *data) {
    const int2 texture_size = (int2) { font_texture_size, font_texture_size };
    const int2 global_position = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 position = get_element_position(global_position, data->canvas.size);
    zox_instance(prefab_zigel)
    zox_name("zigel")
    zox_set(e, ZigelIndex, { data->zigel_index })
    zox_set(e, Color, { data->fill_color })
    zox_set(e, SecondaryColor, { data->outline_color })
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, data->element.size, texture_size, data->element.anchor, data->element.layer, position, global_position);
    return e;
}
