// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_icon(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon")
    zox_add_tag(e, Icon)
    zox_prefab_set(e, ParentLink, { 0 })
    zox_remove_tag(e, FrameTexture)
    zox_add_tag(e, IconTexture)  // general one
    add_selectable_components(world, e);
    zox_prefab_set(e, OutlineColor, {{ 0, 255, 0, 255 }})
    zox_prefab_set(e, FrameCorner, { 16 })
    return e;
}

ecs_entity_t spawn_icon(ecs_world_t *world, SpawnIcon *data) {
    int2 position = data->element.position; // anchor our position
    const int2 position_in_canvas = get_element_pixel_position_global(data->parent.position, data->parent.size, data->element.position, data->element.anchor);
    const float2 real_position = get_element_position(position_in_canvas, data->canvas.size);
    anchor_element_position2D(&position, data->element.anchor, data->element.size);
    zox_instance(data->prefab)
    // zox_name("icon")
    initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, position_in_canvas);
    zox_set(e, Color, { data->icon.fill_color })
    zox_set(e, OutlineColor, { data->icon.outline_color })
    return e;
}
