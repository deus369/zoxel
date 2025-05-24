#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// #define zox_is_flatlands
// todo: spawn stream point and move around
// todo: print out timing per updates
// todo: print out time to load
// todo: test option for headless, if not, spawn window / load shaders

// clear; make prepare game=test_terrain_spawn
// clear; make game=test_terrain_spawn && make run game=test_terrain_spawn

const byte log_meshes = 0;
const byte log_chunks = 0;
const byte log_lods = 0;

byte test_terrain_spawn(ecs_world_t *world) {
    uint lagged_frames = 0;
    const int test_seed = 666;
    const double max_frame_time = 1.0 / 60.0;
    game_name = "test_terrain_spawn";
    zox_log_line("### TEST STARTING ###")
    zox_log_line("  - started [%s]", game_name)
    zox_log_line("  - max frame time [%f]", max_frame_time)
    zox_log_line("  - seed [%i]", test_seed)
    zox_log_line("  - terrain_depth [%i]", terrain_depth)
    zox_log_line("  - render_distance [%i]", render_distance)
    zox_log_line("  - headless [%i]", headless)
    zox_log_line("### ### ### ### ###")
    initialize_networking();
    initialize_voxes(world);
    double test_start = current_time_in_seconds();
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

    double time_since_start = (current_time_in_seconds() - test_start);
    zox_log_line("### ### ### ### ###")
    zox_log_line("! [S]:spawned terrain at frame [%i] time [%f]", ecs_run_count - 1, current_time_in_seconds())

    const ecs_entity_t streamer = spawn_streamer(world, prefab_streamer, int3_zero);
    const ecs_entity_t terrain = spawn_terrain_streaming(world, realm, int3_zero, (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance }, prefab_terrain, prefab_chunk_height);
    zox_set(terrain, RealmLink, { realm })
    zox_set(realm, TerrainLink, { terrain }) // link terrain to realm too
    local_terrain = terrain;
    run_count = 0;
    while (run_count <= 4096) {
        double time_start = current_time_in_seconds();
        update_ecs();
        double time_end = current_time_in_seconds();
        double time_since_start = (time_end - test_start);
        run_count++;
        zox_geter(terrain, ChunkLinks, chunkLinks);
        byte any_chunks_generating = 0;
        int chunk_count = count_int3_hashmap(chunkLinks->value);
        for (int j = 0; j < chunkLinks->value->size; j++) {
            int3_hashmap_pair* pair = chunkLinks->value->data[j];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                ecs_entity_t chunk = pair->value;
                zox_geter_value(chunk, ChunkLodDirty, byte, lod_dirty)
                zox_geter_value(chunk, GenerateChunk, byte, generate_chunk)
                zox_geter_value(chunk, MeshDirty, byte, mesh_dirty)
                zox_geter_value(chunk, ChunkMeshDirty, byte, chunk_mesh_dirty)
                if (log_chunks && generate_chunk == chunk_generate_state_end) {
                    zox_log_line("- f[%i] chunk generated [%f]", ecs_run_count - 1, time_since_start)
                }
                if (log_lods && lod_dirty == chunk_lod_state_end) {
                    zox_log_line("- f[%i] chunk lod finished [%f]", ecs_run_count - 1, time_since_start)
                }
                /*if (log_meshes && mesh_dirty == mesh_dirty_state_end) {
                    zox_log_line("- f[%i] chunk mesh finished [%f]", ecs_run_count - 1, time_since_start)
                }*/
                if (log_meshes && chunk_mesh_dirty == chunk_dirty_state_end) {
                    zox_log_line("- f[%i] chunk mesh finished [%f]", ecs_run_count - 1, time_since_start)
                }
                if (generate_chunk || mesh_dirty || lod_dirty || chunk_mesh_dirty) {
                    any_chunks_generating = 1;
                }

                pair = pair->next;
                checks++;
            }
        }
        double time_taken = (time_end - time_start);
        if (time_taken >= max_frame_time) {
            zox_log_line("! [S]:lagged at frame [%i] chunks [%i] time [%f]", ecs_run_count - 1, chunk_count, time_taken)
            lagged_frames++;
        }
        if (!any_chunks_generating) {
            zox_log_line("+ [S]:finished [f%i] rendered chunks [%i] time [%f]", ecs_run_count - 1, chunk_count, time_since_start)
            break;
        }
    }
    // move stream point
    zox_set(streamer, StreamDirty, { 1 })
    zox_set(streamer, StreamPoint, { (int3) { 1, 0, 0 } })
    time_since_start = (current_time_in_seconds() - test_start);
    zox_log_line("### ### ### ### ###")
    zox_log_line("! [M]:starting update at frame [%i] time [%f]", ecs_run_count - 1, current_time_in_seconds())
    run_count = 0;
    while (run_count <= 256) {
        // process stream movement
        double time_start = current_time_in_seconds();
        update_ecs();
        double time_end = current_time_in_seconds();
        time_since_start = (time_end - test_start);
        run_count++;
        if (run_count <= 1) {
            continue;
        }
        // check chunks
        zox_geter(terrain, ChunkLinks, chunkLinks);
        byte any_chunks_generating = 0;
        int chunk_count = count_int3_hashmap(chunkLinks->value);
        for (int j = 0; j < chunkLinks->value->size; j++) {
            int3_hashmap_pair* pair = chunkLinks->value->data[j];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                ecs_entity_t chunk = pair->value;
                zox_geter_value(chunk, ChunkLodDirty, byte, lod_dirty)
                zox_geter_value(chunk, GenerateChunk, byte, generate_chunk)
                zox_geter_value(chunk, MeshDirty, byte, mesh_dirty)
                zox_geter_value(chunk, ChunkMeshDirty, byte, chunk_mesh_dirty)
                if (log_chunks && generate_chunk == chunk_generate_state_end) {
                    zox_log_line("- f[%i] chunk generated [%f]", ecs_run_count - 1, time_since_start)
                }
                if (log_lods && lod_dirty == chunk_lod_state_end) {
                    zox_log_line("- f[%i] chunk lod finished [%f]", ecs_run_count - 1, time_since_start)
                }
                if (log_meshes && chunk_mesh_dirty == chunk_dirty_state_end) {
                    zox_log_line("- f[%i] chunk mesh finished [%f]", ecs_run_count - 1, time_since_start)
                }
                if (generate_chunk || mesh_dirty || lod_dirty || chunk_mesh_dirty) {
                    any_chunks_generating = 1;
                }
                pair = pair->next;
                checks++;
            }
        }
        double time_taken = (time_end - time_start);
        if (time_taken >= max_frame_time) {
            zox_log_line("! [M]:lagged at frame [%i] chunks [%i] time [%f]", ecs_run_count - 1, chunk_count, time_taken)
            lagged_frames++;
        }
        if (!any_chunks_generating) {
            zox_log_line("+ [M]:finished [f%i] rendered chunks [%i] time [%f]", ecs_run_count - 1, chunk_count, time_since_start)
            break;
        }
    }
    zox_log_line("### ### ### ### ###")

    zox_log_line("> ended [%s]", game_name)
    if (lagged_frames > 10) {
        zox_log_line("### TEST FAILED ###")
    } else if (lagged_frames > 0) {
        zox_log_line("### TEST OKAY ###")
    } else {
        zox_log_line("### TEST SUCCEEDED ###")
    }
    zox_log_line("  - lagged_frames [%i]", lagged_frames)
    zox_log_line("### ### ### ### ###")
    zox_log_line("> exiting game")
    return EXIT_FAILURE; // close game
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    zox_game_type = zox_game_mode_3D;
    boot_event = test_terrain_spawn;
    // terrain_mode = terrain_mode_flatlands;
    headless = 0; // 0 | 1

    // zox_log_terrain_generation = 1;
    /*disable_npcs = 1;
    disable_block_voxes = 1; // fix it's positioning
    disable_block_vox_generation = 1;
    render_distance = 16;
    render_distance_y = 2; // 2 | 8 | 16
    terrain_depth = 4;
    initial_terrain_lod = 3; // 3 | 2
    terrain_lod_dividor = 3; // 2 | 3
    block_vox_depth = 5;
    character_depth = 5;*/

    // terrain
    render_distance = 6; // 2 | 4 | 8 | 16 | 32
    render_distance_y = 2; // 1 | 2 | 8 | 16
    real_chunk_scale = 8.0f; // 4 | 8 | 16 | 32 etc
    initial_terrain_lod = 2; // 3 | 2
    terrain_lod_dividor = 4; // 2 | 3
    terrain_depth = 4;

    // block voes
    block_vox_depth = 5;


    disable_block_vox_generation = 1;
    disable_block_voxes = 1;

    // npcs
    character_depth = 5;
    vox_model_scale = 1 / 32.0f;
    disable_npcs = 1;
}
#endif