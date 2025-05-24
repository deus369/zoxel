// this passes cameras into chunks
// each chunk will calculate distance to nearest camera and based LOD off this distance

void ChunkLodSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) {
        return;
    }
    const byte max_camera_distance = render_distance + 1;
    const byte max_depth = terrain_depth;
    zox_field_world()
    ecs_query_t *streamers_query = it->ctx;
    ecs_iter_t streamers_iter = ecs_query_iter(world, streamers_query);
    ecs_query_next(&streamers_iter);
    if (streamers_iter.count == 0) {
        ecs_iter_fini(&streamers_iter);
        return;
    }
    byte streamers_dirty = 0;
    zox_field_in_iter(&streamers_iter, StreamDirty, streamDirtys, 1)
    for (int i = 0; i < streamers_iter.count; i++) {
        zox_field_i(StreamDirty, streamDirtys, streamDirty)
        if (streamDirty->value == zox_general_state_dirty) {
            streamers_dirty = 1;
            break;
        }
    }
    if (!streamers_dirty) {
        ecs_iter_fini(&streamers_iter);
        return;
    }
    zox_field_in_iter(&streamers_iter, StreamPoint, streamPoints, 2)
    int3 *stream_points = (int3 *) streamPoints;
    zox_field_in(ChunkPosition, chunkPositions, 1)
    zox_field_out(RenderLod, renderLods, 2)
    zox_field_out(ChunkLodDirty, chunkLodDirtys, 3)
    zox_field_out(RenderDistance, renderDistances, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(RenderDistance, renderDistances, renderDistance)
        const int3 stream_point = find_closest_point(stream_points, streamers_iter.count, chunkPosition->value)
        ;
        const byte camera_distance = get_camera_chunk_distance(stream_point, chunkPosition->value);
        if (camera_distance != renderDistance->value) {
            renderDistance->value = camera_distance;
            const byte new_lod =  get_terrain_lod_from_camera_distance(camera_distance, max_camera_distance, max_depth);
            zox_field_o(RenderLod, renderLods, renderLod)
            if (renderLod->value != new_lod) {
                renderLod->value = new_lod;
                if (new_lod != render_lod_invisible) {
                    // when updating lods, we also set dirty
                    zox_field_o(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
                    chunkLodDirty->value = chunk_lod_state_trigger;
                }
            }
        }
    }
    ecs_iter_fini(&streamers_iter);
} zox_declare_system(ChunkLodSystem)