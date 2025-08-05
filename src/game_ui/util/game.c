extern ecs_entity_t spawn_menu_start(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const char *header_label
);

void spawn_players_start_ui(ecs_world_t *world) {
    zox_logv("> spawn_players_start_ui [%i]", players_playing)
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t player = zox_players[i];
        zox_geter_value(player, CanvasLink, ecs_entity_t, canvas);
        zox_logv("    - player [%s] - canvas[%s]", zox_get_name(player), zox_get_name(canvas));
        spawn_menu_start(world, prefab_menu_start, player, canvas, game_name);
    }
}
