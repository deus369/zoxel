// just a panel with a label and a bar
// the bar can be clicked to reposition the handle as well
ecs_entity_t spawn_prefab_slider(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_slider")
    add_ui_plus_components(world, e);
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { default_button_corner })
    zox_prefab_set(e, OutlineThickness, { default_button_frame_thickness })
    zox_prefab_set(e, Color, { default_fill_color })
    zox_prefab_set(e, OutlineColor, { default_outline_color })
    zox_prefab_set(e, ParentLink, { 0 })
    // zox_set(e, Color, { icon_overlay_fill_color })
    // zox_set(e, OutlineColor, { icon_overlay_outline_color })
    // zox_set(e, RenderDisabled, { 0 })
    return e;
}

ecs_entity_t spawn_slider(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data)
{
    zox_instance(element_data.prefab)
    zox_name("slider")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    return e;
}