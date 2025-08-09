// this passes cameras into chunks
// each chunk will calculate distance to nearest camera and based LOD off this distance
const byte disable_chunk_loding = 0;

void ChunkLodSystem(iter *it) {
    if (zox_cameras_disable_streaming) {
        return;
    }
    zox_sys_query()
    // const byte max_camera_distance = terrain_lod_far + 1;
    // const byte max_depth = terrain_depth;
    zox_sys_world()
    byte streamers_dirty = 0;
    int3 *stream_points = NULL;
    int stream_points_length = 0;
    zox_sys_query_begin()
    while (zox_sys_query_loop()) {
        if (streamers_dirty) {
            continue;
        }
        zox_sys_begin_2()
        zox_sys_in_2(StreamPoint)
        zox_sys_in_2(StreamDirty)
        for (int j = 0; j < it2.count; j++) {
            zox_sys_i_2(StreamDirty, streamDirty)
            if (streamDirty->value == zox_general_state_dirty) {
                stream_points = (int3*) StreamPoints_2;
                stream_points_length = it2.count;
                streamers_dirty = 1;
                break;
            }
        }
    }
    zox_sys_query_end()
    if (!streamers_dirty) {
        return;
    }
    zox_sys_begin()
    zox_sys_in(ChunkPosition)
    zox_sys_out(RenderLod)
    zox_sys_out(ChunkLodDirty)
    zox_sys_out(RenderDistance)
    zox_sys_out(RenderDistanceDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_o(RenderLod, renderLod)
        zox_sys_o(ChunkLodDirty, chunkLodDirty)
        zox_sys_o(RenderDistance, renderDistance)
        zox_sys_o(RenderDistanceDirty, renderDistanceDirty)
        const int3 stream_point = find_closest_point(stream_points, stream_points_length, chunkPosition->value)
        ;
        const byte new_render_distance = get_camera_chunk_distance_xz(stream_point, chunkPosition->value);
        // zox_log("At chunk [%ix%ix%i]\n", stream_point.x, stream_point.y, stream_point.z)
        if (new_render_distance != renderDistance->value) {
            renderDistance->value = new_render_distance;
            renderDistanceDirty->value = zox_dirty_trigger;
            if (disable_chunk_loding) {
                continue;
            }
            const byte new_lod = distance_to_terrain_lod(renderDistance->value);
            if (renderLod->value != new_lod) {
                renderLod->value = new_lod;
                if (new_lod != render_lod_invisible) {
                    // when updating lods, we also set dirty
                    chunkLodDirty->value = chunk_lod_state_trigger;
                }
            }
        }
    }
} zoxd_system(ChunkLodSystem)