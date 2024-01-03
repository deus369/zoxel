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
    spawn_default_ui(world);
    zox_spawn_main_menu(world, game_name);
}

void Zoxel2DImport(ecs_world_t *world) {
    zox_module(Zoxel2D)
    boot_event = boot_zoxel2D;
}

#endif
