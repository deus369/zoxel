/*void spawn_character3D_healthbar3D(ecs_world_t *world,
    spawned_character3D_data *data)
{
    if (disable_npc_uis) {
        return;
    }
    if (!zox_valid(data->health)) {
        zox_log_error("invalid stat [health] on character [%s]", zox_get_name(data->e))
        return;
    }
    const float ui_position = statbar_float_position;
    // spawn 3D healtbar
    SpawnDataElementbar3D spawn_data = {
        // .percentage = health.x / health.y,
        .ui_holder = data->e,
        .position_y = ui_position,
        .backbar = {
            .prefab = prefab_statbar3D
        },
        .frontbar = {
            .prefab = prefab_elementbar3D_front
        },
    };
    Text3DData statbar_text_data = {
        .prefab = prefab_text3D
    };
    Zigel3DData statbar_zigel_data = {
        .prefab = prefab_zigel3D,
        .resolution = text3D_resolution,
        .font_thickness = text3D_fill_thickness,
        .font_outline = text3D_outline_thickness,
        .fill_color = statbar3D_font_color_fill,
        .outline_color = statbar3D_font_color_outline
    };
    const entity2 e = spawn_elementbar3(world, &spawn_data, statbar_text_data, statbar_zigel_data);

    zox_set(e.x, StatLink, { data->health })
    zox_set(e.y, StatLink, { data->health })
    zox_set(e.x, ElementHolder, { data->e })
    zox_add_tag(e.y, StatsLabel)
    add_to_ElementLinks(data->elementLinks, e.x);
}*/