// a small square frame ui with an icon in it
// used for game - action/skill/stat - uis
ecs_entity_t spawn_prefab_icon(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon")
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    zox_add_tag(e, Icon)
    zox_add_tag(e, IconTexture)  // general one
    zox_prefab_set(e, IconType, { 0 })
    zox_prefab_set(e, IconIndex, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, Color, { default_fill_color_icon })
    zox_prefab_set(e, OutlineColor, { default_outline_color_icon })
    zox_prefab_set(e, IconRadius, { default_icon_radius })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_icon(ecs_world_t *world,
    SpawnIcon *data)
{
    zox_instance(data->element.prefab)
    zox_name("icon")
    set_element_spawn_data(world, e, data->canvas, data->parent, &data->element);
    zox_set(e, Color, { data->texture.fill_color })
    zox_set(e, OutlineColor, { data->texture.outline_color })
    zox_set(e, IconIndex, { data->index })
    // icons have overlays now
    Children *children = &((Children) { 0, NULL });
    // icon overlay
    ParentSpawnData icon_data = {
        .e = e,
        .position = data->element.position_in_canvas,
        .size = data->element.size
    };
    const ElementSpawnData icon_overlay_data = {
        .prefab = prefab_icon_overlay,
        .layer = data->element.layer + 1,
        .size = data->element.size,
        .anchor = float2_half,
        .render_disabled = 1,
    };
    const ecs_entity_t overlay = spawn_icon_overlay(world,
        data->canvas,
        icon_data,
        icon_overlay_data);
    add_to_Children(children, overlay);
    // set and return
    zox_set(e, Children, { children->length, children->value })
    return e;
}