void spawn_menu_game_stats(ecs_world_t *world, const ecs_entity_t menu_game, const ecs_entity_t player, Children *children) {
    if (!player || !zox_has(player, CharacterLink) || !zox_has(player, CanvasLink)) {
        zox_log_error("! invalid player in [spawn_game_ui_stats]")
        return;
    }
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (!canvas) {
        zox_log_error("! invalid canvas in [spawn_game_ui_stats]")
        return;
    }
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!character || !zox_has(character, StatLinks)) {
        zox_log_error("! invalid character in [spawn_game_ui_stats]")
        return;
    }
    zox_geter(character, StatLinks, stats)
    if (!stats || stats->length <= 1) {
        zox_log_error("! invalid stats in [spawn_game_ui_stats]")
        return;
    }
    const ecs_entity_t health = stats->value[stat_index_health];
    const ecs_entity_t mana = stats->value[stat_index_mana];
    const ecs_entity_t energy = stats->value[stat_index_energy];
    add_to_Children(children, spawn_statbar2D(world, canvas, menu_game, player, (ecs_entity_2) { character, health }, 0));
    add_to_Children(children, spawn_statbar2D(world, canvas, menu_game, player, (ecs_entity_2) { character, energy }, 1));
    add_to_Children(children, spawn_statbar2D(world, canvas, menu_game, player, (ecs_entity_2) { character, mana }, 2));
}