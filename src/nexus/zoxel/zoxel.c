#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// todo: remove boot function
// todo: spawn prefabs after settings are set here

// log types
// #define zox_enable_log_ios
// #define zox_enable_log_input
// #define zox_enable_log_ui
// #define zox_enable_log_shader

// todo: remove this and put into engine
byte boot_zoxel_game(ecs_world_t *world, const ecs_entity_t app) {
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
    spawn_weather(world);
#ifdef zox_mod_space
    if (!headless) {
        spawn_connected_devices(world, app);
        players_playing = spawn_players(world, game);
    }
#endif
#ifdef zox_mod_ui
    spawn_players_cameras_canvases(world, game, players_playing, app);
    spawn_players_start_ui(world);
#endif
#ifdef zox_mod_musics
    spawn_realm_playlist(world, realm);
#endif
    return EXIT_SUCCESS;
}

zox_begin_module(ZoxGame)
    boot_event = boot_zoxel_game;
    // app settings
    headless = 0;

    // issue: npcs can walk outside the bounds of the spawn zone atm, thus making them not be destroyed properly when moving away
    // debug
    // terrain_mode = terrain_mode_flatlands;
    // render_distance_y = 1;
    character_spawn_rate = 4; // 0 | 1 | 16 | 32 | 64 | 128
    is_characters_instanced = 1;
    disable_npc_hooks = 0;
    disable_npc_uis = 0;

    // max npcs
    /*
    terrain_mode = terrain_mode_flatlands;
    character_spawn_rate = 128;
    is_characters_instanced = 1;
    disable_npc_hooks = 1;
    disable_npc_uis = 1;
    */

    disable_npc_positioner = 0;
    // disable_instancing = 1; // test so we can reverse backward etc
    // disable_npc_movement = 1;
    zox_visualize_sounds = 0;
    is_log_gpu_restore = 0;
    // zox_debug_id(Block)
    // zox_debug_print_modules(world, 1);
    // zox_debug_print_systems(world, 1);
    // zox_debug_print_components(world, 1);
    // is_log_io = 1;
    // is_log_sounds = 1;
    // vsync = 0;
    // is_split_screen = 1;
    // fullscreen = 0;

    // Gameplay
    zox_experience_max_start = 10;
    // regen_rate = 10;
    hit_terrain_color = (color) { 2, 185, 145, 155 };
    hit_character_color = (color) { 155, 45, 45, 65 };
    hit_block_vox_color = (color) { 55, 135, 185, 145 };

    // mood
    const float sub_resolution = 4;
    viewport_scale = 1 / sub_resolution;
    grayscale_mode = 0;
    is_generate_vox_outlines = 0;

    // world gen
    block_spawn_chance_grass = 1600; //  512 | 1024 | 2048 | 3000
    terrain_amplifier = 32; // 64;

    // physics
    // target_fps = 15;
    friction3D = 12; // 560;
    air_friction3D = 1; // 40;
    bounce_lost_force = 0.12f;
    // zox_default_gravity.y = -8;
    zox_jump_power = 4;
    run_speed = 1.36;
    run_accceleration = 2.2;
    backwards_multiplier = 0.7f;
    player_movement_power = (float2) { 14, 14 };
    max_velocity3D = (float2) { 1.3f, 1.3f };

    zox_game_type = zox_game_mode_3D;

    menu_sky_color = color_rgb_grayscale(15);
    menu_sky_bottom_color = menu_sky_color;
    fog_color = menu_sky_color;
    viewport_clear_color = menu_sky_color;

    // scaling
    terrain_lod_near = 3;
    real_chunk_scale = 8.0f; // 4 | 8 | 16 | 32
    terrain_depth = 4;
    block_vox_depth = 5;
    character_depth = 5;
    vox_model_scale = 1 / ((float) powers_of_two[character_depth]);

    // render distance settings
    // initial_terrain_lod = 2; // 2 |3
    // terrain_lod_far = 8; // 2 | 4 | 8 | 16 | 32
    block_vox_render_at_lod = 0; // now using lod minimum
    fog_density = 0.034f;
    // character_render_distance = 2;  // 1 | 2

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
    zox_set(prefab_slider, Color, { header_fill })
    zox_set(prefab_slider, OutlineColor, { header_outline })
    zox_set(prefab_handle, Color, { button_font_fill })
    zox_set(prefab_handle, OutlineColor, { button_font_outline })
    // nothing_font_color = debug_color; // debug font texture

    // fix prefabs
    if (prefab_vox) {
        zox_prefab_set(prefab_vox, VoxScale, { vox_model_scale })
    }
    if (prefab_character3) {
        zox_prefab_set(prefab_character3, VoxScale, { vox_model_scale })
    }
    if (prefab_character3_npc) {
        zox_prefab_set(prefab_character3_npc, VoxScale, { vox_model_scale })
    }

    // debug
    disable_block_vox_generation = 0;
    // disable_block_voxes = 1;
    game_rule_attach_to_character = 1;
    disable_npcs = 0;
    game_ui_has_taskbar = 1;
    test_actions_skills = 0;
    test_items_blocks = 1;
    test_all_skills = 1;

    // get_debug_label_app
    // set_prefab_debug_label(world, &get_label_realm_colors);
    // set_prefab_debug_label(world, &get_label_player_element_links);
    // set_prefab_debug_label(world, &get_label_player_stats);
    // set_prefab_debug_label(world, &get_label_player_items);
    // set_prefab_debug_label(world, &get_label_player_skills);
    // set_prefab_debug_label(world, &get_label_player_actions);
    // set_prefab_debug_label(world, &get_label_player_quests);
    // set_prefab_debug_label(world, &debug_label_lods);
    // set_prefab_debug_label(world, &debug_label_collisions);
    set_prefab_debug_label(world, &debug_label_chunk_link);
    // set_prefab_debug_label(world, &debug_label_app);

    // add_hook_key_down(key_down_test_aura);
    add_hook_key_down(toggle_life_terrain);
    add_hook_key_down(toggle_player_death);
    add_hook_key_down(test_game_end);
    add_hook_key_down(test_fall_through_terrain);
    add_hook_key_down(spawn_tilemap_ui);
    add_hook_key_down(toggle_editor);
    add_hook_key_down(toggle_character_particles);
    // test function for npc spawning
    // add_hook_key_down(test_spawn_character_npc);
    // add_hook_key_down(key_down_test_aura);
    add_hook_key_down(key_down_toggle_debug_chunks);
    add_hook_key_down(key_down_toggle_debug_character_bounds);
    add_hook_key_down(key_down_toggle_debug_voxes_bounds);
    // add_hook_key_down(test_spawn_chunk_terrain);
    add_hook_spawned_character3D(&spawn_character_skills);
    // add_hook_key_down(test_key_element_front2D);
    // add_hook_key_down(key_down_update_text3D);
    add_hook_key_down(key_down_toggle_streaming);

    // fades
    is_start_game_delays = 1;
    is_end_game_delays = 1;
zox_end_module(ZoxGame)

#endif