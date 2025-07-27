void HealthbarSpawnerSystem(ecs_iter_t *it) {
    const float ui_position = statbar_float_position;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CombatState)
    zox_sys_in(StatLinks)
    zox_sys_out(ElementLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(CombatState, combat)
        zox_sys_i(StatLinks, stats)
        zox_sys_o(ElementLinks, elementLinks)
        // remove old
        if (combat->value == zox_combat_leaving) {
            // destroy healthbar here
            find_array_component_with_tag(elementLinks, Healthbar, healthbar)
            if (zox_valid(healthbar)) {
                // zox_log("destroying healthbar: %s", zox_get_name(healthbar))
                remove_from_ElementLinks(elementLinks, healthbar);
                zox_delete(healthbar)
            } else {
                zox_log_error("failed to find healthbar..")
            }
            continue;
        }

        // when entering, spawn healthbar
        if (combat->value != zox_combat_enter_battle) {
            continue;
        }
        find_array_component_with_tag(stats, HealthStat, health)
        if (!zox_valid(health)) {
            continue;
        }
        // zox_log("+ spawning healthbar on [%s]", zox_get_name(e))

        // spawn 3D healtbar
        SpawnDataElementbar3D spawn_data = {
            // .percentage = health.x / health.y,
            .ui_holder = e,
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
        const ecs_entity_2 healthbar = spawn_elementbar3(world, &spawn_data, statbar_text_data, statbar_zigel_data);

        zox_set(healthbar.x, StatLink, { health })
        zox_set(healthbar.y, StatLink, { health })
        zox_set(healthbar.x, ElementHolder, { e })
        zox_add_tag(healthbar.y, StatsLabel)
        zox_add_tag(healthbar.x, Healthbar)

        add_to_ElementLinks(elementLinks, healthbar.x);
    }
} zox_declare_system(HealthbarSpawnerSystem)