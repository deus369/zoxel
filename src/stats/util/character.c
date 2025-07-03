const int character_stats = 2;
const int player_extra_stats = 5;
#define statbar_float_position 0.32f

void spawn_new_character_uis(ecs_world_t *world, const ecs_entity_t character, ElementLinks *elementLinks, byte render_disabled, const ecs_entity_t health_stat, float2 health) {
    float ui_position = statbar_float_position;
    // spawn 3D healtbar
    SpawnDataElementbar3D spawn_data = {
        .percentage = health.x / health.y,
        .ui_holder = character,
        .position_y = ui_position,
        .backbar = {
            .prefab = prefab_statbar3D,
            .render_disabled = render_disabled
        },
        .frontbar = {
            .prefab = prefab_elementbar3D_front,
            .render_disabled = render_disabled
        },
    };
    Text3DData statbar_text_data = {
        .prefab = prefab_text3D,
        .text = ""
    };
    Zigel3DData statbar_zigel_data = {
        .prefab = prefab_zigel3D,
        .font_thickness = 12,
        .resolution = 64,
        .fill_color = (color) { 55, 255, 255, 255 },
        .outline_color = color_black
    };
    const ecs_entity_2 e = spawn_elementbar3D(world, &spawn_data, statbar_text_data, statbar_zigel_data);
    zox_prefab_set(e.x, StatLink, { health_stat })
    zox_prefab_set(e.y, StatLink, { health_stat })
    add_to_ElementLinks(elementLinks, e.x);
    zox_set(e.x, ElementHolder, { character })
}

// todo: take in npc spawn meta data, like location, biome, etc
void spawn_character_stats(ecs_world_t *world, spawned_character3D_data *data) {
    // stats
    float2 health = (float2) { 10, 10 };
    health.x = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    int stats_count = character_stats;
    if (data->p) {
        stats_count += player_extra_stats;
    }
    StatLinks *stats = &((StatLinks) { 0, NULL });
    resize_memory_component(StatLinks, stats, ecs_entity_t, stats_count)
    data->stats = stats->value;
    data->stats_count = stats_count;
    // health
    stats->value[0] = spawn_user_stat(world, realm_stat_soul, data->e);
    const ecs_entity_t health_stat = spawn_user_stat(world, realm_stat_health, data->e);
    zox_set(health_stat, StatValue, { health.x })
    zox_set(health_stat, StatValueMax, { health.y })
    stats->value[1] = health_stat;
    // players are richer bbeings from the aether
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
    data->stats_count = stats->length;
    // player character ui
    if (data->p) {
        const ecs_entity_t canvas = zox_get_value(data->p, CanvasLink)
        find_child_with_tag(canvas, MenuGame, game_menu)
        if (game_menu) {
            find_child_with_tag(game_menu, ElementBar, healthbar2D)
            zox_set(healthbar2D, StatLink, { health_stat })
            // set to text
            const Children *statbar2D_children = zox_get(healthbar2D, Children)
            const ecs_entity_t healtbar2D_text = statbar2D_children->value[1];
            zox_set(healtbar2D_text, StatLink, { health_stat })
        } else {
            zox_log("! game_menu not found\n")
        }
    }
    // spawns overhead ui
    spawn_new_character_uis(world, data->e, data->elementLinks, data->render_disabled, health_stat, health);
}