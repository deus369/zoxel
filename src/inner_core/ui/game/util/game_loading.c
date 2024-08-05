// todo: GenerateRealm -> regenerate realm data with new seed
// todo: game start delayed while realm is dirty

void destroy_main_menu(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) return;
    zox_delete(menu)
}

void begin_play_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    set_game_state_target(world, game, zox_game_playing);
}

void button_event_new_game(ecs_world_t *world, const ClickEventData *event) {
    destroy_main_menu(world, event->clicker);
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    realm_save.seed = get_unique_time_seed();
    set_noise_seed(realm_save.seed);
    // todo: i should delete old one here
#ifndef zox_disable_save_games
    delete_save_directory("zoxel");
    create_new_save_directory("zoxel");
    save_realm("zoxel", "seed.dat", &realm_save);
#endif
    zox_set(realm, GenerateRealm, { zox_generate_realm_start })
    begin_play_game(world, event->clicker);
}

void button_event_continue_game(ecs_world_t *world, const ClickEventData *event) {
    destroy_main_menu(world, event->clicker);
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    // todo: spawn realm data like voxels/stats/skills when starting new game
    load_realm("zoxel", "seed.dat", &realm_save);
    set_noise_seed(realm_save.seed);
    zox_set(realm, GenerateRealm, { zox_generate_realm_start })
    begin_play_game(world, event->clicker);
}
