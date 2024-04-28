#ifndef def_zox_game_zoxel2D
#define def_zox_game_zoxel2D

unsigned char boot_zixel(ecs_world_t *world) {
    game_name = "Automata";
    zox_log("Booting [%s]\n", game_name)
    if (initialize_zox(world) == EXIT_FAILURE) return EXIT_FAILURE;
    if (!headless) load_app_icon(main_window, resources_folder_name"textures/game_icon.png");
    // Realm,  players, skybox
    ecs_entity_t realm = spawn_realm(world);
    create_game_stats(world, realm);
    ecs_entity_t game = spawn_game(world);
    zox_set(game, RealmLink, { realm })
    spawn_weather(world);
    if (!headless) spawn_music(world, instrument_piano);
    load_element_styles(world);
    spawn_players_cameras_canvases(world);
    return EXIT_SUCCESS;
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    zox_game_type = zox_game_mode_2D;
    boot_event = boot_zixel;
    menu_sky_color = (float3) { 0.3f, 0.7f, 0.7f };
    menu_sky_bottom_color = (float3) { 0.2f, 0.56f, 0.56f };
    game_sky_color = (float3) { 0.6f, 0.4f, 0.3f };
    game_sky_bottom_color = (float3) { 0.5f, 0.35f, 0.48f };
}

#endif
