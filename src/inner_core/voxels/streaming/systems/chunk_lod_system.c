// this passes cameras into chunks
// each chunk will calculate distance to nearest camera and based LOD off this distance
const unsigned char max_camera_distance = streaming_distance + 1; // 3;

void ChunkLodSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) return;
    zox_iter_world()
    ecs_query_t *streamers_query = it->ctx;
    ecs_iter_t streamers_iter = ecs_query_iter(world, streamers_query);
    ecs_query_next(&streamers_iter);
    if (streamers_iter.count == 0) {
        ecs_iter_fini(&streamers_iter);
        return;
    }
    unsigned char streamers_dirty = 0;
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
        const unsigned char camera_distance = get_camera_chunk_distance(stream_point, chunkPosition->value);
        if (camera_distance != renderDistance->value) {
            renderDistance->value = camera_distance;
            const unsigned char new_lod =  get_terrain_lod_from_camera_distance(camera_distance, max_camera_distance);
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



// zox_log(" > chunk dirty at [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
// also set neighbors to rebuild (chunk dirty)
/*  */
