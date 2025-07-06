#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// clear; make game=test_realm_spawn && make run game=test_realm_spawn

byte test_realm_spawn(ecs_world_t *world) {
    const int test_seed = 666;
    game_name = "test_realm_spawn";
    zox_log("> started [%s]", game_name)
    headless = 1;
    initialize_networking();
    initialize_voxes(world);
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    zox_log("> seed [%i]", test_seed)
    set_noise_seed(test_seed);
    zox_set(realm, GenerateRealm, { zox_generate_realm_start })
    int run_count = 0;
    while (run_count <= 64) {
        zox_geter_value(realm, GenerateRealm, byte, pre_realm_state)
        update_ecs(world;
        if (pre_realm_state == zox_generate_realm_items) {
            zox_geter(realm, ItemLinks, itemLinks)
            zox_log("  - state [%i] items [%i]", pre_realm_state, itemLinks->length)
        }
        run_count++;
        zox_geter_value(realm, GenerateRealm, byte, realm_state);
        zox_log("> run_count [%i] state [%i]", run_count, realm_state)
        if (realm_state == zox_generate_realm_end) {
            break;
        }
    }
    zox_log("> ended [%s]", game_name)
    // print timings per generation
    zox_log("> exiting game")
    return EXIT_FAILURE; // close game
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    zox_game_type = zox_game_mode_3D;
    boot_event = test_realm_spawn;
}
#endif