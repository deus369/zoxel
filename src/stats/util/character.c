const int character_stats = 2;
const int player_extra_stats = 5;
#define statbar_float_position 0.32f

void spawn_character_stats(ecs_world_t *world, spawned_character3D_data *data) {
    if (!zox_valid(realm_stat_soul)) {
        zox_log_error("the realm has invalid stats")
        return;
    }
    // generate numbers here
    float2 health = (float2) { 10, 10 };
    health.x = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;

    data->stats_length = character_stats;
    if (data->p) {
        data->stats_length += player_extra_stats;
    }
    StatLinks *stats = &((StatLinks) { 0, NULL });
    resize_memory_component(StatLinks, stats, ecs_entity_t, data->stats_length)
    data->stats = stats->value;

    // Stat: Soul
    const ecs_entity_t stat_soul = spawn_user_stat(world, realm_stat_soul, data->e);
    stats->value[stat_index_soul] = stat_soul;

    // Stat: Health
    const ecs_entity_t stat_health = spawn_user_stat(world, realm_stat_health, data->e);
    zox_set(stat_health, StatValue, { health.x })
    zox_set(stat_health, StatValueMax, { health.y })
    stats->value[stat_index_health] = stat_health;

    // players are richer beings from the aether
    if (data->p) {
        const ecs_entity_t game = zox_get_value(data->p, GameLink)
        const ecs_entity_t realm = zox_get_value(game, RealmLink)
        zox_geter(realm, StatLinks, realm_stats)
        stats->value[2] = spawn_user_stat(world, realm_stat_mana, data->e);
        const ecs_entity_t stat_energy = spawn_user_stat(world, realm_stat_energy, data->e);
        zox_set(stat_energy, StatValue, { 4 })
        zox_set(stat_energy, StatValueMax, { 12 })
        stats->value[3] = stat_energy;
        stats->value[4] = spawn_user_stat(world, realm_stat_regen_health, data->e);
        stats->value[5] = spawn_user_stat(world, realm_stat_regen_energy, data->e);
        stats->value[6] = spawn_user_stat(world, realm_stat_regen_mana, data->e);
        // add all attributes as 0
        for (int i = 0; i < realm_stats->length; i++) {
            const ecs_entity_t realm_stat = realm_stats->value[i];
            if (!zox_valid(realm_stat)) {
                continue;
            }
            if (zox_has(realm_stat, StatAttribute)) {
                const ecs_entity_t character_stat = spawn_user_stat(world, realm_stat, data->e);
                add_to_StatLinks(stats, character_stat);
            }
        }
    }

    zox_set(data->e, StatLinks, { stats->length, stats->value })
    data->stats = stats->value;
    data->stats_length = stats->length;
    // player character ui
    if (data->p) {
        const ecs_entity_t canvas = zox_get_value(data->p, CanvasLink)
        find_child_with_tag(canvas, MenuGame, game_menu)
        // sometimes its here, sometimes not!
        if (zox_valid(game_menu)) {
            find_child_with_tag(game_menu, ElementBar, healthbar2D)
            if (zox_valid(healthbar2D)) {
                zox_set(healthbar2D, StatLink, { stat_health })
                zox_geter(healthbar2D, Children, statbar2D_children)
                if (statbar2D_children->length >= 1) {
                    const ecs_entity_t healtbar2D_text = statbar2D_children->value[1];
                    zox_set(healtbar2D_text, StatLink, { stat_health })
                }
            }
        }
    }
}