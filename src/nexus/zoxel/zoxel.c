#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// todo: remove boot function
// todo: spawn prefabs after settings are set here

// log types
// #define zox_enable_log_ios
// #define zox_enable_log_input
// #define zox_enable_log_ui
// #define zox_enable_log_shader

byte boot_zoxel_game(ecs_world_t *world) {
    intialize_game_store();
    // test_steam_cloud(); // idk
#ifdef zox_mod_networking
    initialize_networking();
#endif
#ifdef zox_mod_realms
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
#endif
#ifdef zox_mod_games
    game_name = "Zoxel";
    const ecs_entity_t game = spawn_game(world, realm);
#endif
    // game spawning
#ifdef zox_mod_weathers
    spawn_weather(world);
#endif
#ifdef zox_mod_ui
    spawn_players_cameras_canvases(world, game);
    spawn_players_start_ui(world);
#endif
#ifdef zox_mod_musics
    spawn_realm_playlist(world, realm);
#endif
    return EXIT_SUCCESS;
}

zox_begin_module(ZoxGame)
//void ZoxGameImport(ecs_world_t *world) {
//    zox_module(ZoxGame)
    boot_event = boot_zoxel_game;
    zox_debug_id(Block)
    zox_debug_print_modules(world, 1);
    zox_debug_print_systems(world, 1);
    zox_debug_print_components(world, 1);
    // is_log_io = 1;
    // is_log_sounds = 1;
    // terrain_mode = terrain_mode_flatlands;
    headless = 0;
    is_raycast_minivoxes = 1;

    zox_game_type = zox_game_mode_3D;
    menu_sky_color = (color_rgb) { 0, 5, 0 };
    menu_sky_bottom_color = (color_rgb) { 0, 0, 0 };
    set_skybox_colors(world, menu_sky_color, menu_sky_bottom_color);

    // main menu
    // header
    header_fill = color_grayscale(4);
    header_outline = color_grayscale(44);
    // header text
    header_font_resolution = 64;
    header_font_thickness_fill = 4;
    header_font_thickness_outline = 4;
    header_font_fill = color_grayscale(32);
    header_font_outline = color_grayscale(122);
    // window
    window_fill = color_grayscale(10);
    window_outline = color_grayscale(44);
    // buttons
    button_fill = color_grayscale(10);
    button_outline = color_grayscale(44);
    // button text
    button_font_resolution = 16;
    button_font_thickness_fill = 1;
    button_font_thickness_outline = 2;
    button_font_fill = color_grayscale(44);
    button_font_outline = color_grayscale(122);
    // set them again for now
    zox_set(prefab_ui_list, Color, { window_fill })
    zox_set(prefab_ui_list, OutlineColor, { window_outline })
    zox_set(prefab_header, Color, { header_fill })
    zox_set(prefab_header, OutlineColor, { header_outline })
    // nothing_font_color = debug_color; // debug font texture

    // scaling
    real_chunk_scale = 8.0f; // 4 | 8 | 16 | 32
    terrain_depth = 4;
    block_vox_depth = 5;
    character_depth = 5;
    vox_model_scale = 1 / 32.0f;

    // world gen
    block_spawn_chance_grass = 3000; // 1024;
    terrain_amplifier = 32;

    // physics
    friction3D = 1800; // 560;
    air_friction3D = 320; // 40;
    zox_jump_power = 146; // 124.0f
    // zox_default_gravity.y = -8;
    bounce_lost_force = 0.3f;

    // render distance settings
    initial_terrain_lod = 2; // 2 |3
    terrain_lod_dividor = 2; // 2 | 3 | 4
    render_distance = 10; // 2 | 4 | 8 | 16 | 32
    render_distance_y = 2; // 1 | 2 | 4
    block_vox_render_at_lod = 0; // now using lod minimum
    fog_density = 0.034f;
    character_render_distance = 2;  // 1 | 2
    characters_per_chunk_count = 2; // 0 | 1 | 4 | 8 | 16 | 64

    // fix prefabs
    if (prefab_vox) {
        zox_prefab_set(prefab_vox, VoxScale, { vox_model_scale })
    }
    if (prefab_character3D) {
        zox_prefab_set(prefab_character3D, VoxScale, { vox_model_scale })
    }
    if (prefab_character3D_npc) {
        zox_prefab_set(prefab_character3D_npc, VoxScale, { vox_model_scale })
    }

    // debug
    is_generate_vox_outlines = 0;
    disable_block_vox_generation = 0;
    // disable_block_voxes = 1;
    game_rule_attach_to_character = 1;
    disable_npcs = 0;
    game_ui_has_taskbar = 1;
    test_actions_skills = 0;
    test_items_blocks = 1;
    test_all_skills = 1;

    // set_prefab_debug_label(world, &get_label_realm_colors);
    // set_prefab_debug_label(world, &get_label_player_element_links);
    // set_prefab_debug_label(world, &get_label_player_stats);
    // set_prefab_debug_label(world, &get_label_player_items);
    // set_prefab_debug_label(world, &get_label_player_skills);
    // set_prefab_debug_label(world, &get_label_player_actions);
    // set_prefab_debug_label(world, &get_label_player_quests);
    set_prefab_debug_label(world, &get_label_player_chunk_link);

    // fades
    is_start_game_delays = 1;
    is_end_game_delays = 1;
zox_end_module(ZoxGame)

#endif