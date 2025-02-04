void realms_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t game) {
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    // spawn_terrain(
    const ecs_entity_t terrain = spawn_terrain_streaming(world, realm, int3_zero, (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance }, prefab_terrain, prefab_chunk_height);
    zox_set(terrain, RealmLink, { realm })
    zox_set(realm, TerrainLink, { terrain }) // link terrain to realm too
    local_terrain = terrain;

    // testing transform on new worlds!
    /*float3 second_world_position = (float3) { 0, -10000, 0 };
    float4 second_world_rotation = (float4) { 0, 0, 0, 1 };
    float3 second_world_scale = (float3) { 0.5f, 0.5f, 0.5f };
    const ecs_entity_t second_world = create_terrain(world, realm, int3_zero, (int3) { terrain_spawn_distance, terrain_vertical, terrain_spawn_distance }, prefab_terrain, prefab_chunk_height, );*/
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

void realms_game_state(ecs_world_t *world, const ecs_entity_t game, const unsigned char old_game_state, const unsigned char new_game_state) {
    if (old_game_state == zox_game_start && new_game_state == zox_game_playing) realms_start_game(world, game);
    else if (new_game_state == zox_game_start) realms_game_end(world, game);
}
