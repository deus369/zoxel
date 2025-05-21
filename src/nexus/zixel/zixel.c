#ifndef zox_mod_game
#define zox_mod_game

byte boot_zixel(ecs_world_t *world) {
    game_name = "zixel";
    zox_log(" + booting [%s]\n", game_name)
    #ifdef zox_mod_voxels
    initialize_voxes(world);
    #endif
    // Realm,  players, skybox
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
    spawn_weather(world);
    // if (!headless) spawn_music(world, prefab_music);
    spawn_players_cameras_canvases(world, game);
    spawn_players_start_ui(world);
    // spawn_character2D(world, prefab_character2D, float2_zero);
    return EXIT_SUCCESS;
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    zox_game_type = zox_game_mode_2D;
    boot_event = boot_zixel;
    headless = 0;
    menu_sky_color = (float3) { 0.3f, 0.7f, 0.7f };
    menu_sky_bottom_color = (float3) { 0.2f, 0.56f, 0.56f };
    game_sky_color = (float3) { 0.6f, 0.4f, 0.3f };
    game_sky_bottom_color = (float3) { 0.5f, 0.35f, 0.48f };
}

#endif
