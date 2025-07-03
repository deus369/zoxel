void spawn_character3D_healthbar3D(ecs_world_t *world, spawned_character3D_data *data) {
    const ecs_entity_t health_stat = data->stats[1];
    // find_array_component_with_tag2(data->stats, data->stats_count, HealthStat, health_stat)
    if (!zox_valid(health_stat)) {
        zox_log("! health stat not found [spawn_character3D_healthbar3D].\n")
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
        .font_thickness = text3D_thickness,
        .font_outline = text3D_outline,
        .resolution = text3D_resolution,
        .fill_color = (color) { 55, 255, 255, 200 },
        .outline_color = color_black
    };
    const ecs_entity_2 e = spawn_elementbar3D(world, &spawn_data, statbar_text_data, statbar_zigel_data);
    add_to_ElementLinks(data->elementLinks, e.x);
    zox_set(e.x, StatLink, { health_stat })
    zox_set(e.y, StatLink, { health_stat })
    zox_set(e.x, ElementHolder, { data->e })
    zox_add_tag(e.y, StatsLabel)
}