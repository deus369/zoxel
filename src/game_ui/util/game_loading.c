// todo: GenerateRealm -> regenerate realm data with new seed
// todo: game start delayed while realm is dirty

void destroy_player_main_menu(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) {
        zox_log_error("main menu not found")
        return;
    } else {
        zox_delete(menu)
    }
}

void begin_play_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    zox_set(game, GameStateTarget, { zox_game_load })
}

void button_event_new_game(ecs_world_t *world, const ClickEventData *event) {
    destroy_player_main_menu(world, event->clicker);
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    realm_save.seed = get_unique_time_seed();
    set_noise_seed(realm_save.seed);
    // todo: i should delete old one here
#ifndef zox_disable_save_games
    delete_save_directory(game_name);
    create_new_save_directory(game_name);
    save_realm(game_name, "seed.dat", &realm_save);
#endif
    zox_set(realm, Seed, { realm_save.seed })
    begin_play_game(world, event->clicker);
}

void button_event_continue_game(ecs_world_t *world, const ClickEventData *event) {
    destroy_player_main_menu(world, event->clicker);
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    // todo: spawn realm data like voxels/stats/skills when starting new game
    load_realm(game_name, "seed.dat", &realm_save);
    set_noise_seed(realm_save.seed);
    zox_set(realm, Seed, { realm_save.seed })
    begin_play_game(world, event->clicker);
}
