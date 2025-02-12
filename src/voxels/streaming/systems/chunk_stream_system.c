// if camera distance is less than max view distance
// spawn a chunk neighbor if any dont exist
//  - only if visible too
const byte streaming_distance = 2;
extern ecs_entity_t prefab_chunk_height;
extern ecs_entity_t spawn_chunk_terrain(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t terrain, const int3 camera_position, const int3 chunk_position, const float real_chunk_scale);

void ChunkStreamSystem(ecs_iter_t *it) {
    zox_iter_world()
    ecs_query_t *streamers_query = it->ctx;
    ecs_iter_t streamers_iter = ecs_query_iter(world, streamers_query);
    ecs_query_next(&streamers_iter);
    if (streamers_iter.count == 0) {
        ecs_iter_fini(&streamers_iter);
        return;
    }
    zox_field_in_iter(&streamers_iter, StreamPoint, streamPoints, 1)
    int3 *stream_points = (int3 *) streamPoints;
    zox_field_in(ChunkPosition, chunkPositions, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_in(RenderDistance, renderDistances, 3)
    zox_field_out(ChunkNeighbors, chunkNeighborss, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_o(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        if (renderDistance->value == 255) continue;
        const byte stay_zone = renderDistance->value < streaming_distance;
        const byte kill_zone = !stay_zone; // renderDistance->value > streaming_distance + 1;
        if (!stay_zone) {
            if (kill_zone) {
                zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
                int3_hashmap_remove(chunkLinks->value, chunkPosition->value);
                zox_delete(it->entities[i])
            }
            continue;   // only grow chunks in centre of map
        }
        zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
        for (int j = 0; j < chunkNeighbors->length; j++) {
            if (zox_valid(chunkNeighbors->value[j])) continue;
            const int3 neighbor_position = int3_add(chunkPosition->value, int3_directions[j]);
            ecs_entity_t neighbor = int3_hashmap_get(chunkLinks->value, neighbor_position);
            if (!neighbor) {
                const int3 stream_point = find_closest_point(stream_points, streamers_iter.count, chunkPosition->value);
                neighbor = spawn_chunk_terrain(world, prefab_chunk_height, voxLink->value, stream_point, neighbor_position, real_chunk_scale);
                int3_hashmap_add(chunkLinks->value, neighbor_position, neighbor);
            }
            chunkNeighbors->value[j] = neighbor;
        }
    }
} zox_declare_system(ChunkStreamSystem)
