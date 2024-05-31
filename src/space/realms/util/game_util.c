void realms_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t game) {
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    const ecs_entity_t terrain = create_terrain(world, realm, int3_zero, (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance });
    zox_set(terrain, RealmLink, { realm })
    zox_set(realm, TerrainLink, { terrain }) // link terrain to realm too
    local_terrain = terrain;
}

void realms_start_game2D_delayed(ecs_world_t *world, const ecs_entity_t game) {
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    spawn_grid2D(world);
}

void realms_start_game(ecs_world_t *world, const ecs_entity_t game) {
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &realms_start_game3D_delayed, game, 1.2f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &realms_start_game2D_delayed, game, 1.2f);
    }
    unlock_achievement("test_achievement"); // idk if this can be per player
}

void realms_game_end_delayed(ecs_world_t *world, const ecs_entity_t game) {
    if (zox_game_type == zox_game_mode_3D) {
        zox_delete_and_set(local_terrain)
        destroy_terrain_grid(world);
    }
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
}

void realms_game_end(ecs_world_t *world, const ecs_entity_t game) {
    delay_event(world, &realms_game_end_delayed, game, 1.2f);
}

void realms_game_state(ecs_world_t *world, ecs_entity_t game, unsigned char new_game_state) {
    unsigned char previous_game_state = zox_get_value(game, GameState)
    if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) realms_start_game(world, game);
    else if (new_game_state == zox_game_start) realms_game_end(world, game);
}
