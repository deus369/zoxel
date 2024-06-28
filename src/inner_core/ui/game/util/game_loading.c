GameSave player_save;

extern void respawn_realm_voxels(ecs_world_t *world, const ecs_entity_t realm);

void destroy_main_menu(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) return;
    zox_delete(menu)
}

void begin_play_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    trigger_event_game(world, game, zox_game_playing);
}

void button_event_new_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)

    int seed = (int) get_unique_time_seed();
    player_save.seed = seed;
    set_noise_seed(player_save.seed);

    create_new_save_directory("zoxel");
    save_game("zoxel", "seed.dat", &player_save);

    respawn_realm_voxels(world, realm);

    // begin_play_game(world, player);
    destroy_main_menu(world, player);
    delay_event(world, &begin_play_game, player, 0.1f);
}

void button_event_continue_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)

    // todo: spawn realm data like voxels/stats/skills when starting new game
    load_game("zoxel", "seed.dat", &player_save);
    set_noise_seed(player_save.seed);

    respawn_realm_voxels(world, realm);

    // begin_play_game(world, player);
    destroy_main_menu(world, player);
    delay_event(world, &begin_play_game, player, 0.1f);
}
