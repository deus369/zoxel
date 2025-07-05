void spawn_character3D_healthbar3D(ecs_world_t *world, spawned_character3D_data *data) {
    const ecs_entity_t health_stat = data->stats[stat_index_health];
    if (!zox_valid(health_stat)) {
        zox_log_error("health stat not found [spawn_character3D_healthbar3D]")
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
    const ecs_entity_2 e = spawn_elementbar3D(world, &spawn_data, statbar_text_data, statbar_zigel_data);
    add_to_ElementLinks(data->elementLinks, e.x);
    zox_set(e.x, StatLink, { health_stat })
    zox_set(e.y, StatLink, { health_stat })
    zox_set(e.x, ElementHolder, { data->e })
    zox_add_tag(e.y, StatsLabel)
}