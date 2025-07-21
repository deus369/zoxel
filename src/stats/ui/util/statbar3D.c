void spawn_character3D_healthbar3D(ecs_world_t *world, spawned_character3D_data *data) {
    /*zox_geter(data->realm, StatLinks, realm_stats)
    ecs_entity_t realm_health = 0;
    for (int i = 0; i < realm_stats->length; i++) {
        const ecs_entity_t stat = realm_stats->value[i];
        if (!realm_health && zox_has(stat, StatState)) {
            realm_health = stat;
        }
    }
    // now get health stat
    for (int i = 0; i < data->stats->length; i++) {
        const ecs_entity_t stat = data->stats->value[i];
    }*/

    // const ecs_entity_t stat_health = stat_index_health < data->stats_length ? data->stats[stat_index_health] : 0;
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
    const ecs_entity_2 e = spawn_elementbar3D(world, &spawn_data, statbar_text_data, statbar_zigel_data);
    add_to_ElementLinks(data->elementLinks, e.x);
    zox_set(e.x, StatLink, { data->health })
    zox_set(e.y, StatLink, { data->health })
    zox_set(e.x, ElementHolder, { data->e })
    zox_add_tag(e.y, StatsLabel)
}