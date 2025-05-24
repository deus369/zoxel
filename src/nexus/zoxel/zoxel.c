#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// todo: initialize event modules can hook onto for loading i/o
//      - should occur after all modules are imported, but before game is booted
// - each module should add to a load resources event for i/o game data
// #define zox_log_boot_game
// #define zox_enable_log_start_game

byte boot_zoxel_game(ecs_world_t *world) {
    game_name = "Zoxel";
    zox_log_start_game("> boot started [%s]", game_name)
    initialize_networking();
    intialize_game_store();
    #ifdef zox_mod_voxels
        initialize_voxes(world);
    #endif
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
    zox_log_start_game("> boot completed [zoxel]")
    // game spawning
    #ifdef zox_mod_weathers
        spawn_weather(world);
    #endif
    #ifdef zox_mod_musics
        spawn_realm_playlist(world, realm);
    #endif
    #ifdef zox_mod_players
        spawn_players_cameras_canvases(world, game);
        spawn_players_start_ui(world);
    #endif
    test_steam_cloud(); // idk
    return EXIT_SUCCESS;
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    boot_event = boot_zoxel_game;
    zox_game_type = zox_game_mode_3D;
    game_ui_has_taskbar = 1;
    menu_sky_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32  / 255.0f };
    menu_sky_bottom_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32 / 255.0f };
    // terrain_mode = terrain_mode_flatlands;

    headless = 0;

    // wait this breaks terrain mesh at 4 depth

    // terrain
    initial_terrain_lod = 2; // 3 | 2
    terrain_lod_dividor = 4; // 2 | 3
    render_distance = 6; // 2 | 4 | 8 | 16 | 32
    render_distance_y = 2; // 1 | 2 | 4
    real_chunk_scale = 8.0f; // 4 | 8 | 16 | 32
    terrain_depth = 4;

    // block voxes
    disable_block_vox_generation = 1;
    disable_block_voxes = 1;
    block_vox_depth = 5;

    // npcs
    disable_npcs = 1;
    character_depth = 5;
    vox_model_scale = 1 / 32.0f;

    zox_prefab_set(prefab_vox, VoxScale, { vox_model_scale })
    zox_prefab_set(prefab_character3D, VoxScale, { vox_model_scale })
    zox_prefab_set(prefab_character3D_npc, VoxScale, { vox_model_scale })

    // todo: set block vox resolution to 5
    // todo: use component max depths on terrain
    // todo: fix the texture blocks - use textures generate a regular vox model

    is_generate_vox_outlines = 0;
}

#endif