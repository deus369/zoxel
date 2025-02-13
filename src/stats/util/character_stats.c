const int character_stats = 2;
const int player_extra_stats = 6;

// todo: take in npc spawn meta data, like location, biome, etc
ecs_entity_t spawn_character_stats(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player, const byte render_disabled) {
    // stats
    float health = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    float max_health = 10.0f;
    int stats_count = character_stats;
    if (player) stats_count += player_extra_stats;
    StatLinks *statLinks = zox_get_mut(e, StatLinks)
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
    const ecs_entity_t statbar = spawn_elementbar3D(world, prefab_statbar3D, e, health / max_health, render_disabled);
    zox_prefab_set(statbar, StatLink, { health_stat })
    ElementLinks *elementLinks = zox_get_mut(e, ElementLinks)
    resize_memory_component(ElementLinks, elementLinks, ecs_entity_t, 1)
    elementLinks->value[0] = statbar;
    zox_modified(e, ElementLinks)
    if (player) {
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        find_child_with_tag(canvas, MenuGame, game_menu)
        if (game_menu) {
            find_child_with_tag(game_menu, ElementBar, healthbar_2D)
            zox_set(healthbar_2D, StatLink, { health_stat })
        }
    }
#endif
    return health_stat;
}
