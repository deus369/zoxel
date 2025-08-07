entity spawn_icon(ecs *world, SpawnIcon *data) {
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
    const entity overlay = spawn_icon_overlay(world,
        data->canvas,
        icon_data,
        icon_overlay_data);
    add_to_Children(children, overlay);
    // set and return
    zox_set(e, Children, { children->length, children->value })
    return e;
}