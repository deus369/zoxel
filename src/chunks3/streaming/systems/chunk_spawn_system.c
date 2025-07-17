extern ecs_entity_t spawn_chunk_terrain(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t terrain, const int3 camera_position, const int3 chunk_position, const float real_chunk_scale);

void ChunkSpawnSystem(ecs_iter_t *it) {
    zox_sys_query()
    zox_field_world()
    const byte log_individuals = 0;
    uint spawned_chunks = 0;
    int3 *stream_points = NULL;
    int stream_points_length = 0;
    byte iterated = 0;
    zox_sys_query_begin()
    while (zox_sys_query_loop()) {
        if (!iterated) {
            iterated = 1;
            zox_field_in_iter(&it2, StreamPoint, streamPoints, 1)
            stream_points = (int3*) streamPoints;
            stream_points_length = it2.count;
        }
    }
    zox_sys_query_end()
    if (stream_points_length == 0) {
        return;
    }
    zox_field_in(ChunkPosition, chunkPositions, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_in(RenderDistance, renderDistances, 3)
    zox_field_out(ChunkNeighbors, chunkNeighborss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
        if (!zox_valid(voxLink->value)) {
            continue;
        }
        // Pass if loading chunk
        if (renderDistance->value == 255) {
            continue;
        }
        // Pass if lod changing
        zox_geter_value(e, ChunkLodDirty, byte, chunkLodDirty)
        if (chunkLodDirty != 0) {
            continue;
        }
        // const int3 stream_point2 = find_closest_point(stream_points, stream_points_length, chunkPosition->value);
        // const byte camera_distance = get_camera_chunk_distance_xz(stream_point2, chunkPosition->value);
        const byte stream_zone = renderDistance->value < terrain_lod_far;
        if (stream_zone) {
            for (byte j = 0; j < 6; j++) {
                ecs_entity_t neighbor = chunkNeighbors->value[j];
                // no need to spawn if neighbor exists
                if (zox_valid(neighbor)) {
                    continue;
                }
                // get position of neighbor and check terrain for it
                const int3 neighbor_position = int3_add(chunkPosition->value, int3_directions[j]);
                if (!(neighbor_position.y >= -render_distance_y && neighbor_position.y <= render_distance_y)) {
                    continue;
                }
                zox_geter(voxLink->value, ChunkLinks, oldChunkLinks)
                neighbor = int3_hashmap_get(oldChunkLinks->value, neighbor_position);
                // if not existing yet, spawn a new chunk
                if (!zox_valid(neighbor)) {
                    const int3 stream_point = find_closest_point(stream_points, stream_points_length, neighbor_position);
                    // only spawn new chunk if within stream distance
                    const byte camera_distance = get_camera_chunk_distance_xz(stream_point, neighbor_position);
                    if (camera_distance <= terrain_lod_far) {
                        neighbor = spawn_chunk_terrain(world,
                            prefab_chunk_streaming,
                            voxLink->value,
                            stream_point,
                            neighbor_position,
                            real_chunk_scale);
                        zox_geter(voxLink->value, ChunkLinks, chunkLinks)
                        // zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
                        int3_hashmap_add(chunkLinks->value, neighbor_position, neighbor);
                        if (log_individuals) {
                            zox_log_streaming("+ streaming: new [%i]s chunk [%ix%ix%i]", spawned_chunks, neighbor_position.x, neighbor_position.y, neighbor_position.z)
                        }
                        spawned_chunks++;
                    }
                }
                chunkNeighbors->value[j] = neighbor;
            }
        }
    }
    if (spawned_chunks > 0) {
        zox_log_streaming(" + [%i] spawned [%i]", ecs_run_count, spawned_chunks)
    }
} zox_declare_system(ChunkSpawnSystem)