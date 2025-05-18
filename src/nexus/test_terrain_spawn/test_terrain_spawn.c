#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// todo: spawn stream point and move around
// todo: print out timing per updates
// todo: print out time to load
// todo: test option for headless, if not, spawn window / load shaders

// clear; make prepare game=test_terrain_spawn
// clear; make game=test_terrain_spawn && make run game=test_terrain_spawn

byte test_terrain_spawn(ecs_world_t *world) {
    const int test_seed = 666;
    game_name = "test_terrain_spawn";
    zox_log_line("> started [%s]", game_name)
    zox_log_line("> seed [%i]", test_seed)
    headless = 1;
    initialize_networking();
    initialize_voxes(world);
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
    set_noise_seed(test_seed);
    zox_set(realm, GenerateRealm, { zox_generate_realm_start })
    int run_count = 0;
    while (run_count <= 64) {
        update_ecs();
        zox_geter_value(realm, GenerateRealm, byte, realm_state);
        if (realm_state == zox_generate_realm_end) {
            break;
        }
        run_count++;
    }

    const ecs_entity_t terrain = spawn_terrain_streaming(world, realm, int3_zero, (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance }, prefab_terrain, prefab_chunk_height);
    zox_set(terrain, RealmLink, { realm })
    zox_set(realm, TerrainLink, { terrain }) // link terrain to realm too
    local_terrain = terrain;
    run_count = 0;
    while (run_count <= 32) {
        update_ecs();
        run_count++;
        zox_geter(terrain, ChunkLinks, chunkLinks);
        int chunk_count = count_int3_hashmap(chunkLinks->value);
        zox_log_line("> run_count [%i] chunks [%i]", run_count, chunk_count)
    }

    zox_log_line("> ended [%s]", game_name)
    zox_log_line("> exiting game")
    return EXIT_FAILURE; // close game
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    zox_game_type = zox_game_mode_3D;
    boot_event = test_terrain_spawn;
}
#endif