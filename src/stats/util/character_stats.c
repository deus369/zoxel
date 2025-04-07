const int character_stats = 2;
const int player_extra_stats = 6;

void spawn_new_character_uis(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player, byte render_disabled, const ecs_entity_t health_stat, float health, float max_health) {
    float ui_position = 0.43f;
    if (player) {
        ui_position = 0.6f;
    }
    // spawn 3D healtbar
    SpawnDataElementbar3D spawn_data = {
        .percentage = health / max_health,
        .ui_holder = e,
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
        .text = "health [10/10 "
    };
    Zigel3DData statbar_zigel_data = {
        .font_thickness = 12,
        .resolution = 128,
        .prefab = prefab_zigel3D,
        .fill_color = (color) { 55, 255, 255, 255 },
        .outline_color = color_black
    };
    const ecs_entity_2 spawned_elementbar3D = spawn_elementbar3D(world, &spawn_data, statbar_text_data, statbar_zigel_data);
    zox_prefab_set(spawned_elementbar3D.x, StatLink, { health_stat })
    zox_prefab_set(spawned_elementbar3D.y, StatLink, { health_stat })
    ElementLinks *elementLinks = &((ElementLinks) { 0, NULL });
    resize_memory_component(ElementLinks, elementLinks, ecs_entity_t, 1)
    elementLinks->value[0] = spawned_elementbar3D.x;
    zox_set(e, ElementLinks, { elementLinks->length, elementLinks->value })
}

// todo: take in npc spawn meta data, like location, biome, etc
ecs_entity_t spawn_character_stats(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player, const byte render_disabled) {
    // stats
    float max_health = 10.0f;
    float health = max_health;
    health =  (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    int stats_count = character_stats;
    if (player) {
        stats_count += player_extra_stats;
    }
    StatLinks *statLinks = &((StatLinks) { 0, NULL });
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
    zox_set(e, StatLinks, { statLinks->length, statLinks->value })
    // character ui
#ifndef zox_disable_statbars
    if (player) {
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
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
    spawn_new_character_uis(world, e, player, render_disabled, health_stat, health, max_health);
#endif
    return health_stat;
}
