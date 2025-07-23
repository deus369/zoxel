const int character_stats = 2;
#define statbar_float_position 0.32f

void spawn_character_stats(ecs_world_t *world,
    spawned_character3D_data *data)
{
    zox_geter(data->realm, StatLinks, realm_stats)
    ecs_entity_t realm_soul = 0;
    ecs_entity_t realm_health = 0;
    ecs_entity_t realm_energy = 0;
    ecs_entity_t realm_mana = 0;
    for (int i = 0; i < realm_stats->length; i++) {
        const ecs_entity_t stat = realm_stats->value[i];
        if (!realm_soul && zox_has(stat, StatLevel)) {
            realm_soul = stat;
        }
        if (!realm_health && zox_has(stat, StatState)) {
            realm_health = stat;
        } else if (!realm_energy && zox_has(stat, StatState)) {
            realm_energy = stat;
        } else if (!realm_mana && zox_has(stat, StatState)) {
            realm_mana = stat;
        }
    }
    if (!zox_valid(realm_soul)) {
        zox_log_error("the realm has invalid stats")
        return;
    }

    // generate numbers here
    float soul_value = data->soul_value;
    float2 health = (float2) { 5, 5 + soul_value * 5 };
    health.x = randf_range(5, health.y);

    data->stats_length = character_stats;
    int i = 0;
    StatLinks *stats = &((StatLinks) { 0, NULL });
    resize_memory_component(StatLinks, stats, ecs_entity_t, data->stats_length)
    data->stats = stats->value;

    // Stat: Soul
    const ecs_entity_t stat_soul = spawn_user_stat(world, realm_soul, data->e);
    zox_set(stat_soul, StatValue, { soul_value })
    stats->value[i++] = stat_soul;

    // Stat: Health
    const ecs_entity_t stat_health = spawn_user_stat(world, realm_health, data->e);
    zox_set(stat_health, StatValue, { health.x })
    zox_set(stat_health, StatValueMax, { health.y })
    stats->value[i++] = stat_health;
    data->health = stat_health;

    // players are richer beings from the aether
    if (data->p) {
        // zox_geter(realm, StatLinks, realm_stats)
        const ecs_entity_t stat_mana = spawn_user_stat(world, realm_mana, data->e);
        add_to_StatLinks(stats, stat_mana);
        const ecs_entity_t stat_energy = spawn_user_stat(world, realm_energy, data->e);
        zox_set(stat_energy, StatValue, { 4 })
        zox_set(stat_energy, StatValueMax, { 12 })
        add_to_StatLinks(stats, stat_energy);

        /*stats->value[4] = spawn_user_stat(world, realm_stat_regen_health, data->e);
        stats->value[5] = spawn_user_stat(world, realm_stat_regen_energy, data->e);
        stats->value[6] = spawn_user_stat(world, realm_stat_regen_mana, data->e);*/

        // add all attributes as 0
        for (int i = 0; i < realm_stats->length; i++) {
            const ecs_entity_t stat = realm_stats->value[i];
            if (!zox_valid(stat)) {
                continue;
            }
            if (zox_has(stat, StatRegen)) {
                const ecs_entity_t character_stat = spawn_user_stat(world, stat, data->e);
                add_to_StatLinks(stats, character_stat);
            } else if (zox_has(stat, StatAttribute)) {
                const ecs_entity_t character_stat = spawn_user_stat(world, stat, data->e);
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