// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_icon(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon")
    zox_add_tag(e, Icon)
    zox_add_tag(e, IconTexture)  // general one
    zox_prefab_set(e, IconType, { 0 })
    zox_prefab_set(e, IconIndex, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    zox_set(e, Color, { default_fill_color_icon })
    zox_set(e, OutlineColor, { default_outline_color_icon })
    zox_set(e, IconRadius, { default_icon_radius })
    return e;
}

ecs_entity_t spawn_icon(ecs_world_t *world, SpawnIcon *data) {
    int2 position = data->element.position; // anchor our position
    const int2 position_in_canvas = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 real_position = get_element_position(position_in_canvas, data->canvas.size);
    anchor_element_position2D(&position, data->element.anchor, data->element.size);
    zox_instance(data->element.prefab)
    initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->texture_size, data->element.anchor, data->element.layer, real_position, position_in_canvas);
    zox_set(e, Color, { data->texture.fill_color })
    zox_set(e, OutlineColor, { data->texture.outline_color })
    zox_set(e, IconIndex, { data->index })
    return e;
}
