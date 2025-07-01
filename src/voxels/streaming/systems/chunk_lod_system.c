// this passes cameras into chunks
// each chunk will calculate distance to nearest camera and based LOD off this distance
const byte disable_chunk_loding = 0;

void ChunkLodSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) {
        return;
    }
    ecs_query_t *query = it->ctx;
    if (!query) {
        return;
    }
    const byte max_camera_distance = render_distance + 1;
    const byte max_depth = terrain_depth;
    zox_field_world()
    byte streamers_dirty = 0;
    int3 *stream_points = NULL;
    int stream_points_length = 0;
    ecs_iter_t streamers_iter = ecs_query_iter(world, query);
    while (ecs_query_next(&streamers_iter)) {
        if (streamers_dirty) {
            continue;
        }
        zox_field_in_iter(&streamers_iter, StreamPoint, streamPoints, 1)
        zox_field_in_iter(&streamers_iter, StreamDirty, streamDirtys, 2)
        for (int i = 0; i < streamers_iter.count; i++) {
            zox_field_i(StreamDirty, streamDirtys, streamDirty)
            if (streamDirty->value == zox_general_state_dirty) {
                stream_points = (int3*) streamPoints;
                stream_points_length = streamers_iter.count;
                streamers_dirty = 1;
                break;
            }
        }
    }
    ecs_iter_fini(&streamers_iter);
    if (!streamers_dirty) {
        return;
    }
    zox_field_in(ChunkPosition, chunkPositions, 1)
    zox_field_out(RenderLod, renderLods, 2)
    zox_field_out(ChunkLodDirty, chunkLodDirtys, 3)
    zox_field_out(RenderDistance, renderDistances, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(RenderDistance, renderDistances, renderDistance)
        const int3 stream_point = find_closest_point(stream_points, stream_points_length, chunkPosition->value)
        ;
        const byte new_render_distance = get_camera_chunk_distance_xz(stream_point, chunkPosition->value);
        // zox_log("At chunk [%ix%ix%i]\n", stream_point.x, stream_point.y, stream_point.z)
        if (new_render_distance != renderDistance->value) {
            renderDistance->value = new_render_distance;
            if (disable_chunk_loding) {
                continue;
            }
            const byte new_lod =  get_terrain_lod_from_camera_distance(renderDistance->value, max_camera_distance, max_depth);
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
} zox_declare_system(ChunkLodSystem)