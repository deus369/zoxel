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
        if (!zox_valid(chunk)) {
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
        .chunk_position = chunk_position,
        .position = spawn_position,
        .rotation = quaternion_identity,
    };
}

void game_start_player_new_positioner(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    TerrainPlace spawn_place = find_position_in_terrain(world, terrain);
    if (!zox_valid(spawn_place.chunk)) {
        zox_log_error("+ placement failure: player character placed into [%ix%ix%i]", spawn_place.chunk_position.x, spawn_place.chunk_position.y, spawn_place.chunk_position.z)
    } else {
        zox_set(character, Position3D, { spawn_place.position })
        zox_set(camera, Position3D, { spawn_place.position })
    }
}

ecs_entity_t game_start_player_new(ecs_world_t *world,
    const ecs_entity_t player)
{
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
    // spawn a column of chunks for new player:
    zox_mut_begin(terrain, ChunkLinks, chunkLinks)
    byte did_add = 0;
    for (int i = -render_distance_y; i <= render_distance_y * 2; i++) {
        int3 chunk_position = (int3) { 0, i, 0 };
        ecs_entity_t chunk = int3_hashmap_get(chunkLinks->value, chunk_position);
        if (!zox_valid(chunk)) {
            chunk = spawn_chunk_terrain(world,
                    prefab_chunk_height,
                    terrain,
                    chunk_position,
                    chunk_position,
                    real_chunk_scale);
            if (zox_valid(chunk)) {
                int3_hashmap_add(
                    chunkLinks->value,
                    chunk_position,
                    chunk);
                // zox_log("+ spawning chunk for player character loading [%ix%ix%i]:%lu", chunk_position.x, chunk_position.y, chunk_position.z, spawn_place.chunk)
            }
        }
    }
    if (did_add) {
        zox_mut_end(terrain, ChunkLinks)
    }
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    const float3 fake_spawn_position = (float3) { 4, 4, 4 };
    const int3 chunk_position = real_position_to_chunk_position(fake_spawn_position, chunk_dimensions, depth);
    spawn_character3D_data spawn_data = {
        .player = player,
        .vox = vox,
        .terrain = terrain,
        .rotation = quaternion_identity,
        .position = fake_spawn_position,
        // .chunk_position = chunk_position,
        // .terrain_chunk = spawn_place.chunk,
    };
    const ecs_entity_t e = spawn_character3D_player(world, spawn_data);
    delay_event(world, &game_start_player_new_positioner, player, 0.5);
    delay_event(world, &spawn_player_game_ui, player, 0.5);
    return e;
}