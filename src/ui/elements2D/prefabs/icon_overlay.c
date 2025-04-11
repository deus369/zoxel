ecs_entity_t spawn_prefab_icon_overlay(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_overlay")
    zox_prefab_set(e, ParentLink, { 0 })
    zox_set(e, Color, { icon_overlay_fill_color })
    zox_set(e, OutlineColor, { icon_overlay_outline_color })
    zox_set(e, RenderDisabled, { 0 })
    return e;
}

ecs_entity_t spawn_icon_overlay(ecs_world_t *world, const CanvasSpawnData canvas_data, const ParentSpawnData parent_data, const ElementSpawnData element_data) {
    zox_instance(element_data.prefab)
    zox_name("icon_overlay")
    const int2 position_in_canvas = get_element_pixel_position_global(parent_data.position, parent_data.size, element_data.position, element_data.anchor);
    const float2 real_position = get_element_position(position_in_canvas, canvas_data.size);
    // anchor our position
    int2 position = element_data.position;
    anchor_element_position2D(&position, element_data.anchor, element_data.size);
    initialize_element(world, e, parent_data.e, canvas_data.e, position, element_data.size, element_data.size, element_data.anchor, element_data.layer, real_position, position_in_canvas);
    zox_set(e, RenderDisabled, { 1 })
    /*zox_set(e, Color, { data->texture.fill_color })
    zox_set(e, OutlineColor, { data->texture.outline_color })*/
    return e;
}