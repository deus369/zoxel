ecs_entity_t spawn_button(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data,
    const SpawnTextData zext_data,
    const SpawnButtonData button_data)
{
    int text_length = zext_data.text != NULL ? strlen(zext_data.text) : 0;
    const int2 zext_size = (int2) {
        zext_data.font_size * text_length,
        zext_data.font_size
    };
    element_data.size = (int2) {
        zext_size.x + zext_data.padding.x * 2,
        zext_size.y + zext_data.padding.y * 2
    };

    zox_instance(element_data.prefab)
    zox_name("button")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);

    zox_set(e, Color, { button_data.fill })
    zox_set(e, OutlineColor, { button_data.outline })

    Children *children = &((Children) { 0, NULL });

    // text
    SpawnZext spawnZext = {
        .canvas = canvas_data,
        .parent = {
            .e = e,
            .position = element_data.position_in_canvas,
            .size = element_data.size
        },
        .element = {
            .prefab = button_data.prefab_zext,
            .layer = element_data.layer + 1,
            .anchor = float2_half,
            .size = zext_size,
            .render_disabled = element_data.render_disabled,
        },
        .zext = zext_data,
    };
    const ecs_entity_t zext = spawn_zext(world, &spawnZext);
    add_to_Children(children, zext);

    zox_set(e, Children, { children->length, children->value })
    return e;
}