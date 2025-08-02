ecs_entity_t spawn_header3(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data,
    const SpawnButtonData close_button,
    const SpawnTextData zext,
    const SpawnHeaderData header)
{
    zox_instance(element_data.prefab)
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    zox_name("header")
    zox_set(e, DraggedLink, { parent_data.e })
    // zox_log("[%s] is now dragging [%s]", zox_get_name(e), zox_get_name(parent_data.e))

    Children *children = &((Children) { 0, NULL });

    // # Header Text #
    const int string_length = strlen(zext.text);
    int2 zext_position = (int2) {
        ((zext.font_size * string_length) / 2) + header.margins,
        0
    };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!header.is_close_button) {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    SpawnZext zextSpawnData = {
        .canvas = canvas_data,
        .parent = {
            .e = e,
            .position = element_data.position_in_canvas,
            .size = element_data.size,
        },
        .element = {
            .prefab = header.prefab_zext,
            .layer = element_data.layer + 1,
            .anchor = zext_anchor,
            .position = zext_position
        },
        .zext = zext
    };
    const ecs_entity_t header_zext = spawn_zext(world, &zextSpawnData);
    add_to_Children(children, header_zext);

    // # Header Close Button #
    if (header.is_close_button) {
        const byte2 padding = (byte2) {
            (int) (zext.font_size * 0.3f),
            (int) (zext.font_size * 0.3f)
        };
        const int2 close_button_position = (int2) {
            - (zext.font_size / 2) - header.margins,
            0
        };
        add_to_Children(children, spawn_close_button(world, e,
            canvas_data.e,
            element_data.position_in_canvas,
            element_data.size,
            close_button_position,
            zext.font_size,
            padding,
            element_data.layer + 2,
            canvas_data.size));
    }

    zox_set(e, Children, { children->length, children->value })
    return e;
}