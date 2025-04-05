const int character_stats = 2;
const int player_extra_stats = 6;

// todo: take in npc spawn meta data, like location, biome, etc
ecs_entity_t spawn_character_stats(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player, const byte render_disabled) {
    // stats
    float health = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    float max_health = 10.0f;
    int stats_count = character_stats;
    if (player) stats_count += player_extra_stats;

    StatLinks *statLinks = &((StatLinks) { 0, NULL });
    // StatLinks *statLinks = zox_get_mut(e, StatLinks)
    resize_memory_component(StatLinks, statLinks, ecs_entity_t, stats_count)
    // health
    statLinks->value[0] = spawn_user_stat(world, meta_stat_soul, e);
    const ecs_entity_t health_stat = spawn_user_stat(world, meta_stat_health, e);
    zox_set(health_stat, StatValue, { health })
    zox_set(health_stat, StatValueMax, { max_health })
    statLinks->value[1] = health_stat;
    // players are richer bbeings from the aether
    if (player) {
        statLinks->value[2] = spawn_user_stat(world, meta_stat_mana, e);
        statLinks->value[3] = spawn_user_stat(world, meta_stat_energy, e);
        statLinks->value[4] = spawn_user_stat(world, meta_stat_regen_health, e);
        statLinks->value[5] = spawn_user_stat(world, meta_stat_regen_energy, e);
        statLinks->value[6] = spawn_user_stat(world, meta_stat_regen_mana, e);
        statLinks->value[7] = spawn_user_stat(world, meta_stat_strength, e);
    }
    zox_modified(e, StatLinks)
    // character ui
#ifndef zox_disable_statbars
    float ui_position = 0.43f;
    if (player) ui_position = 0.57f;
    SpawnDataElementbar3D spawn_data = {
        .canvas = {
            .ui_holder = e,
            .position_y = ui_position
        },
        .backbar = {
            .prefab = prefab_statbar3D,
            .render_disabled = render_disabled
        },
        .frontbar = {
            .prefab = prefab_elementbar3D_front,
            .render_disabled = render_disabled
        },
        .text = {
            .prefab = prefab_text3D,
            .render_disabled = render_disabled
        },
        .zigel = {
            .prefab = prefab_zigel3D,
            .render_disabled = render_disabled
        },
        .meta = {
            .percentage = health / max_health
        }
    };
    const ecs_entity_t statbar = spawn_elementbar3D(world, &spawn_data);
    zox_prefab_set(statbar, StatLink, { health_stat })
    ElementLinks *elementLinks = &((ElementLinks) { 0, NULL });
    // ElementLinks *elementLinks = zox_get_mut(e, ElementLinks)
    resize_memory_component(ElementLinks, elementLinks, ecs_entity_t, 1)
    elementLinks->value[0] = statbar;
    zox_set(e, ElementLinks, { elementLinks->length, elementLinks->value })
    // zox_modified(e, ElementLinks)
    if (player) {
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        find_child_with_tag(canvas, MenuGame, game_menu)
        if (game_menu) {
            find_child_with_tag(game_menu, ElementBar, healthbar_2D)
            zox_set(healthbar_2D, StatLink, { health_stat })
        }
    }
    zox_set(e, StatLinks, { statLinks->length, statLinks->value })
#endif
    return health_stat;
}
