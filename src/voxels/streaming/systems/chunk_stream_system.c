extern ecs_entity_t prefab_chunk_height;
extern ecs_entity_t spawn_chunk_terrain(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t terrain, const int3 camera_position, const int3 chunk_position, const float real_chunk_scale);

void ChunkStreamSystem(ecs_iter_t *it) {
    zox_field_world()
    ecs_query_t *streamers_query = it->ctx;
    ecs_iter_t streamers_iter = ecs_query_iter(world, streamers_query);
    ecs_query_next(&streamers_iter);
    if (streamers_iter.count == 0) {
        ecs_iter_fini(&streamers_iter);
        return;
    }
    zox_field_in_iter(&streamers_iter, StreamPoint, streamPoints, 1)
    int3 *stream_points = (int3*) streamPoints;
    zox_field_in(ChunkPosition, chunkPositions, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_in(RenderDistance, renderDistances, 3)
    zox_field_out(ChunkNeighbors, chunkNeighborss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) {
            continue;
        }
        // if loading chunk, don't process
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        if (renderDistance->value == 255) {
            continue;
        }
        const byte kill_zone = renderDistance->value > streaming_distance; // + 1;
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        if (kill_zone) {
            zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
            int3_hashmap_remove(chunkLinks->value, chunkPosition->value);
            zox_delete(it->entities[i])
            #ifdef zox_enable_log_streaming
                zox_geter_value(it->entities[i], ChunkPosition, int3, chunk_position)
                zox_log_streaming("- remove chunk [%ix%ix%i]", chunk_position.x, chunk_position.y, chunk_position.z)
            #endif
        } else {
            const byte stream_zone = 1; // renderDistance->value < streaming_distance;
            if (stream_zone) {
                zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
                zox_field_o(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
                for (byte j = 0; j < chunkNeighbors->length; j++) {
                    ecs_entity_t neighbor = chunkNeighbors->value[j];
                    // no need to spawn if neighbor exists
                    if (zox_valid(neighbor)) {
                        continue;
                    }
                    // get position of neighbor and check terrain for it
                    const int3 neighbor_position = int3_add(chunkPosition->value, int3_directions[j]);
                    neighbor = int3_hashmap_get(chunkLinks->value, neighbor_position);
                    // if not existing yet, spawn a new chunk
                    if (!neighbor) {
                        const int3 stream_point = find_closest_point(stream_points, streamers_iter.count, neighbor_position);
                        // only spawn new chunk if within stream distance
                        const byte camera_distance = get_camera_chunk_distance(stream_point, neighbor_position);
                        if (camera_distance <= streaming_distance) {
                            neighbor = spawn_chunk_terrain(world, prefab_chunk_height, voxLink->value, stream_point, neighbor_position, real_chunk_scale);
                            int3_hashmap_add(chunkLinks->value, neighbor_position, neighbor);
                            zox_log_streaming("+ new chunk [%ix%ix%i]", neighbor_position.x, neighbor_position.y, neighbor_position.z)
                        }
                    }
                    chunkNeighbors->value[j] = neighbor;
                }
            }
        }
    }
} zox_declare_system(ChunkStreamSystem)
