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
    if (!zox_valid(character) || !zox_has(character, StatLinks)) {
        zox_log_error("! invalid character in [spawn_game_ui_stats]")
        return;
    }
    zox_geter(character, StatLinks, stats)
    int j = 0;
    byte has_created_soul_ui = 0;
    for (int i = 0; i < stats->length; i++) {
        const ecs_entity_t stat = stats->value[i];
        if (zox_has(stat, StatState)) {
            zox_geter_value(stat, ColorRGB, color_rgb, c)
            const ecs_entity_t statbar = spawn_statbar2D(world, canvas, menu_game, player, (ecs_entity_2) { character, stat }, c, j++);
            add_to_Children(children, statbar);
        }
        if (!has_created_soul_ui && zox_has(stat, StatLevel)) {
            has_created_soul_ui = 1;
            zox_geter_value(stat, ColorRGB, color_rgb, c)
            const ecs_entity_t statbar = spawn_statbar2D(world, canvas, menu_game, player, (ecs_entity_2) { character, stat }, c, j++);
            add_to_Children(children, statbar);
        }
    }
}