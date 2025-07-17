// called from game state changes
void spawn_in_game_ui(ecs_world_t *world, const ecs_entity_t player) {
#ifdef zox_disable_player_ui
    return;
#endif
    if (!zox_has(player, DeviceMode) || !zox_has(player, CanvasLink)) {
        zox_log("! invalid player in [spawn_in_game_ui]\n")
        return;
    }
    const byte device_mode = zox_get_value(player, DeviceMode)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    byte is_touch = device_mode == zox_device_mode_touchscreen;
    #ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
    #endif
    zox_geter(player, CharacterLink, characterLink)
    spawn_menu_game(world, prefab_menu_game, player, characterLink->value);
    if (is_touch) {
        spawn_in_game_ui_touch(world, player, canvas);
    }
}

void spawn_player_game_ui(ecs_world_t *world, const ecs_entity_t player) {
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
    const VoxelNode *chunk_above = NULL;
    byte node_depth = 0;
    byte found_position = 0;
    for (int i = render_distance_y; i >= -render_distance_y; i--) {
        chunk_position.y = i;
        chunk = int3_hashmap_get(chunk_links->value, chunk_position);
        if (!chunk) {
            continue;
        }
        zox_geter(chunk, VoxelNode, chunkd)
        node_depth = zox_get_value(chunk, NodeDepth)
        local_position = find_position_on_ground(chunkd, node_depth, chunk_above, spawns_in_air);
        if (!byte3_equals(byte3_full, local_position)) {
            found_position = 1;
            break;
        }
        chunk_above = chunkd;
    }
    if (!found_position) {
        zox_log_error("failed finding spawn position for player")
    }
    int chunk_length = powers_of_two[node_depth];
    const int3 chunk_dimensions = (int3) { chunk_length, chunk_length, chunk_length };
    const int3 chunk_voxel_position = get_chunk_voxel_position(chunk_position, chunk_dimensions);
    const float3 spawn_position = local_to_real_position_character(local_position, chunk_voxel_position, bounds, node_depth, 1); // voxScale->value);

    // zox_log("Terrain Place Found [%fx%fx%f]", spawn_position.x, spawn_position.y, spawn_position.z)

    spawn_arrow3D(world, spawn_position, (float3) { 0, 4, 0}, 0.5f, 6, 60);

    return (TerrainPlace) {
        .chunk = chunk,
        .position = spawn_position,
        .rotation = quaternion_identity,
    };
}

// called on spawn terrain event

// NOTE: WE NOW NEED TO SPAWN TERRAIN CHUNK HERE IF IT DOESN"T EXIST!
//      - streaming breaks if all chunks die..
ecs_entity_t spawn_character3D_player_in_terrain(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(player_vox_model));
    if (!vox) {
        zox_log_error("[tall_cube] not found on player")
    }
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) {
        return 0;
    }
    const ecs_entity_t game = zox_get_value(player, GameLink)
    if (!game) {
        return 0;
    }
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    if (!realm) {
        return 0;
    }
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) {
        return 0;
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
        spawn_place.chunk = 0;
        load_character_p(
            &spawn_place.position,
            &spawn_place.euler,
            &spawn_place.rotation);
    }

    // if character not in chunk, spawn one here
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    const int3 chunk_position = real_position_to_chunk_position(spawn_place.position, chunk_dimensions, depth);
    zox_mut_begin(terrain, ChunkLinks, chunkLinks)
    spawn_place.chunk = int3_hashmap_get(chunkLinks->value, chunk_position);
    // check if exists first
    if (!zox_valid(spawn_place.chunk)) {
        spawn_place.chunk = spawn_chunk_terrain(world,
            prefab_chunk_height,
            terrain,
            chunk_position,
            chunk_position,
            real_chunk_scale);
        if (zox_valid(spawn_place.chunk)) {
            int3_hashmap_add(chunkLinks->value,
                chunk_position,
                spawn_place.chunk);
            zox_mut_end(terrain, ChunkLinks)
            // zox_log("+ spawning chunk for player character loading [%ix%ix%i]:%lu", chunk_position.x, chunk_position.y, chunk_position.z, spawn_place.chunk)
        } else {
            zox_log_error("failed to spawn chunk [%ix%ix%i]:%lu", chunk_position.x, chunk_position.y, chunk_position.z, spawn_place.chunk)
        }
    } else {
        zox_log("+ player character placed into [%ix%ix%i]", chunk_position.x, chunk_position.y, chunk_position.z)
    }
    spawn_character3D_data spawn_data = {
        .vox = vox,
        .terrain = terrain,
        .terrain_chunk = spawn_place.chunk,
        .chunk_position = chunk_position,
        .position = spawn_place.position,
        .rotation = spawn_place.rotation,
        .euler = spawn_place.euler,
        .player = player,
    };
    zox_set(camera, Position3D, { spawn_place.position }) // reposition camera too
    const ecs_entity_t e = spawn_character3D_player(world, spawn_data);
    if (zox_valid(spawn_place.chunk)) {
        zox_mut_begin(spawn_place.chunk, EntityLinks, entityLinks)
        if (add_to_EntityLinks(entityLinks, e)) {
            zox_mut_end(spawn_place.chunk, EntityLinks)
        }
    }
    zox_set(e, PlayerLink, { player })
    zox_set(e, CameraLink, { camera })
    zox_set(player, CharacterLink, { e })
    attach_camera_to_character(world, player, camera, e);
#ifndef zox_disable_save_games
    if (!is_new_game) {
        delay_event(world, &load_player_e, player, 0.5f);
    }
#endif
    delay_event(world, &spawn_player_game_ui, player, 0.01);
    return e;
}