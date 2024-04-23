#ifndef def_zox_game_zoxel2D
#define def_zox_game_zoxel2D

const char *game_name = "Automata";

unsigned char boot_zoxel2D(ecs_world_t *world) {
    zox_log("Booting zoxel 2D\n")
    if (initialize_zox(world) == EXIT_FAILURE) return EXIT_FAILURE;
    if (!headless) load_app_icon(main_window, resources_folder_name"textures/game_icon.png");
    // Realm,  players, skybox
    ecs_entity_t realm = spawn_realm(world);
    create_game_stats(world, realm);
    ecs_entity_t game = spawn_game(world);
    zox_set(game, RealmLink, { realm })
    spawn_weather(world);
    if (!headless) spawn_music(world, instrument_piano);
    spawn_players(world);
    spawn_player_cameras(world);
    ecs_entity_t canvas = spawn_default_ui(world);
    zox_spawn_main_menu(world, game_name, canvas);
    return EXIT_SUCCESS;
}

void Zoxel2DImport(ecs_world_t *world) {
    zox_module(Zoxel2D)
    zox_game_type = zox_game_mode_2D;
    boot_event = boot_zoxel2D;
    menu_sky_color = (float3) { 0.3f, 0.7f, 0.7f };
    menu_sky_bottom_color = (float3) { 0.2f, 0.56f, 0.56f };
    game_sky_color = (float3) { 0.6f, 0.4f, 0.3f };
    game_sky_bottom_color = (float3) { 0.5f, 0.35f, 0.48f };
}

#endif
