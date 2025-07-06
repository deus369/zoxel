void post_player_start_game(ecs_world_t *world, const ecs_entity_t player) {
    spawn_in_game_ui(world, player);
#ifdef zox_mod_actions_ui
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuActions, menu_actions)
    if (!menu_actions) {
        spawn_player_menu_actions(world, player);
    }
#endif
}

TerrainPlace find_position_in_terrain(ecs_world_t *world, const ecs_entity_t terrain) {
    const float3 bounds = (float3) { 0.5f, 1.0, 0.5f };
    // zox_geter(terrain, VoxScale, voxScale)
    zox_geter(terrain, ChunkLinks, chunk_links)
    byte spawns_in_air = 0;
    ecs_entity_t chunk = 0;
    int3 chunk_position = int3_zero;
    byte3 local_position = byte3_zero;
    const ChunkOctree *chunk_above = NULL;
    byte found_position = 0;
    for (int i = render_distance_y; i >= -render_distance_y; i--) {
        chunk_position.y = i;
        chunk = int3_hashmap_get(chunk_links->value, chunk_position);
        if (!chunk) {
            continue;
        }
        zox_geter(chunk, ChunkOctree, chunkd)
        local_position = find_position_on_ground(chunkd, chunkd->linked, chunk_above, spawns_in_air);
        if (!byte3_equals(byte3_full, local_position)) {
            found_position = 1;
            break;
        }
        chunk_above = chunkd;
    }
    if (!found_position) {
        zox_log_error("failed finding spawn position for player")
    }
    const byte depth = chunk_above != NULL ? chunk_above->linked : 0;
    int chunk_length = powers_of_two[depth];
    const int3 chunk_dimensions = (int3) { chunk_length, chunk_length, chunk_length };
    const int3 chunk_voxel_position = get_chunk_voxel_position(chunk_position, chunk_dimensions);
    const float3 spawn_position = local_to_real_position_character(local_position, chunk_voxel_position, bounds, depth, 1); // voxScale->value);

    // zox_log("Terrain Place Found [%fx%fx%f]", spawn_position.x, spawn_position.y, spawn_position.z)

    spawn_arrow3D(world, spawn_position, (float3) { 0, 4, 0}, 0.5f, 6, 60);

    return (TerrainPlace) {
        .chunk = chunk,
        .spawn_position = spawn_position,
        .spawn_rotation = quaternion_identity,
    };
}

// called on spawn terrain event

// NOTE: WE NOW NEED TO SPAWN TERRAIN CHUNK HERE IF IT DOESN"T EXIST!
//      - streaming breaks if all chunks die..

void spawn_character3D_player_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(player_vox_model));
    if (!vox) {
        zox_log_error("[tall_cube] not found on player")
    }
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) {
        return;
    }
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game) {
        return;
    }
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm) {
        return;
    }
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) {
        return;
    }
    byte is_new_game = 1;
#ifndef zox_disable_save_games
    is_new_game = !has_save_game_file(game_name, "player.dat");
#endif
    TerrainPlace spawn_place;
    if (is_new_game) {
        spawn_place = find_position_in_terrain(world, terrain);
    } else {
        // get character position/rotation
        load_character_p(&spawn_place.spawn_position, &spawn_place.spawn_rotation);
    }
    spawn_character3D_data spawn_data = {
        .vox = vox,
        .terrain = terrain,
        .position = spawn_place.spawn_position,
        .rotation = spawn_place.spawn_rotation,
        .player = player,
    };
    const ecs_entity_t e = spawn_character3D_player(world, spawn_data);
    zox_set(e, ChunkLink, { spawn_place.chunk })
    zox_set(player, CharacterLink, { e })
    zox_set(e, PlayerLink, { player })
    zox_set(e, CameraLink, { camera })
    attach_camera_to_character(world, player, camera, e);
#ifndef zox_disable_save_games
    if (!is_new_game) {
        delay_event(world, &load_player_e, player, 0.01f);
    } else {
        delay_event(world, &save_player_e, player, 2);
    }
#endif
    delay_event(world, &post_player_start_game, player, 0.1);
}

void on_spawned_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    #ifdef zox_disable_player_character
        attach_camera_to_character(world, player, camera, 0);
    #else
        if (game_rule_attach_to_character) {
            spawn_character3D_player_in_terrain(world, player);
        } else {
            attach_camera_to_character(world, player, camera, 0);
        }
    #endif
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    play_playlist(world, realm, 1);
}

void fix_camera_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = (int3) { powers_of_two[depth], powers_of_two[depth], powers_of_two[depth] };
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 position = zox_get_value(camera, Position3D)
    int3 terrain_position = real_position_to_chunk_position(position, chunk_dimensions, terrain_depth);
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game || !zox_has(game, RealmLink)) {
        return;
    }
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm || !zox_has(realm, TerrainLink)) {
        return;
    }
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) {
        return;
    }
    zox_set(camera, StreamPoint, { terrain_position })
    zox_set(camera, VoxLink, { terrain })
    zox_set(camera, StreamDirty, { zox_general_state_trigger })
    zox_set(terrain, EventInput, { player })
    zox_set(terrain, StreamEndEvent, { on_spawned_terrain })
    // zox_log("+ terrain spawning started at [%f]", zox_current_time)
}

// spawn character and set camera to streaming terrain
void player_start_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    float3 spawn_position = (float3) { 8, 8.5f, 8 };
    float4 spawn_rotation = quaternion_identity;
#ifndef zox_disable_save_games
    const byte is_new_game = !has_save_game_file(game_name, "player.dat");
    if (!is_new_game) {
        load_character_p(&spawn_position, &spawn_rotation);
    }
#endif
    zox_set(camera, Position3D, { spawn_position })
    zox_set(camera, Rotation3D, { spawn_rotation })
    delay_event(world, &fix_camera_in_terrain, player, 0.01f);
}