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

void button_event_new_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    destroy_main_menu(world, player);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)

    int seed = (int) get_unique_time_seed();
    realm_save.seed = seed;
    set_noise_seed(realm_save.seed);

    // todo: i should delete old one here
    delete_save_directory("zoxel");
    create_new_save_directory("zoxel");
    save_realm("zoxel", "seed.dat", &realm_save);

    zox_set(realm, GenerateRealm, { zox_generate_realm_start })
    // respawn_realm_voxels(world, realm);
    // delay_event(world, &respawn_realm_items, realm, 0.1f);
    // respawn_realm_items(world, realm);

    begin_play_game(world, player);
    // delay_event(world, &begin_play_game, player, 0.15f);
}

void button_event_continue_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    destroy_main_menu(world, player);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)

    // todo: spawn realm data like voxels/stats/skills when starting new game
    load_realm("zoxel", "seed.dat", &realm_save);
    set_noise_seed(realm_save.seed);

    // zox_log(" > realm start [%lu] %s\n", realm, zox_get_name(realm))
    zox_set(realm, GenerateRealm, { zox_generate_realm_start })
    // respawn_realm_voxels(world, realm);
    // delay_event(world, &respawn_realm_items, realm, 0.1f);
    // respawn_realm_items(world, realm);

    begin_play_game(world, player);
    // delay_event(world, &begin_play_game, player, 0.15f);
}
