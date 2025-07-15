#ifndef zox_mod_game
#define zox_mod_game

// Realm,  players, skybox
byte boot_zixel(ecs_world_t *world) {
    game_name = "zixel";
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
    spawn_weather(world);
    spawn_players_cameras_canvases(world, game);
    spawn_players_start_ui(world);
    // if (!headless) spawn_music(world, prefab_music);
    // spawn_character2D(world, prefab_character2D, float2_zero);
    return EXIT_SUCCESS;
}

zox_begin_module(ZoxGame)
    zox_game_type = zox_game_mode_2D;
    boot_event = boot_zixel;
    headless = 0;
    menu_sky_color = (color_rgb) { 33, 33, 166 };
    menu_sky_bottom_color = (color_rgb) { 33, 33, 166 };
    game_sky_color = (color_rgb) { 22, 177, 33 };
    game_sky_bottom_color = (color_rgb) { 22, 177, 33 };
    set_prefab_debug_label(world, &get_label_character2_player);
zox_end_module(ZoxGame)

#endif
