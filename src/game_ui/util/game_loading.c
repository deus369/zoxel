void destroy_player_main_menu(
    ecs_world_t *world,
    const ecs_entity_t player
) {
    zox_geter(player, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuMain, menu);
    if (!menu) {
        zox_log_error("main menu not found")
        return;
    } else {
        zox_delete(menu)
    }
}

void button_event_continue_game(
    ecs_world_t *world,
    const ClickEventData *event
) {
    destroy_player_main_menu(world, event->clicker);
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    // todo: spawn realm data like voxels/stats/skills when starting new game
    load_realm(game_name, "seed.dat", &realm_save);
    set_noise_seed(realm_save.seed);
    zox_set(realm, Seed, { realm_save.seed })
    zox_set(game, GameStateTarget, { zox_game_load })
}
