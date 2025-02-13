// this checcks neighbor chunks and makes sure surrounding ones update too (i think?)
/*
#define check_chunk_lod(dir)\
    (zox_valid(chunkNeighbors->value[direction_##dir]) &&\
    zox_gett_value(chunkNeighbors->value[direction_##dir], RenderLod) != \
    get_camera_chunk_distance(stream_point, int3_move_##dir(chunk_position)))

// todo: crashes here! find out why with drmemory

// For each terrain, it uses it's Chunks and StreamerLinks

void TerrainLodSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) return;
    zox_iter_world()
    ctx2 *filters = (ctx2 *) it->ctx;
    ecs_query_t *streamers_query = filters->y;
    ecs_iter_t streamers_iter = ecs_query_iter(world, streamers_query);
    ecs_query_next(&streamers_iter);
    int total_streamers = streamers_iter.count;
    if (total_streamers == 0) {
        ecs_iter_fini(&streamers_iter);
        return;
    }
    // dont i need to iterate multiple tables here?
    ecs_query_t *chunks_query = filters->x;
    ecs_iter_t chunks_iterator = ecs_query_iter(world, chunks_query);
    ecs_query_next(&chunks_iterator);
    int total_chunks = chunks_iterator.count;
    if (total_chunks == 0) {
        ecs_iter_fini(&chunks_iterator);
        return;
    }
    const int stream_points_length = total_streamers;
    zox_field_out(StreamDirty, streamDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(StreamDirty, streamDirtys, streamDirty)
        if (!streamDirty->value) continue;
        zox_field_in_iter(&streamers_iter, StreamPoint, streamPoints, 1)
        int3 *stream_points = (int3 *) streamPoints;
        zox_field_in_iter(&chunks_iterator, ChunkPosition, chunkPositions, 1)
        zox_field_in_iter(&chunks_iterator, ChunkNeighbors, chunkNeighborss, 2)
        zox_field_out_iter(&chunks_iterator, RenderLod, renderLods, 3)
        zox_field_out_iter(&chunks_iterator, ChunkDirty, chunkDirtys, 4)
        zox_field_out_iter(&chunks_iterator, ChunkLodDirty, chunkLodDirtys, 5)
        // remember: first pass uses RenderLod of neighbors for checks
        unsigned char camera_distances[total_chunks];
        memset(camera_distances, 255, total_chunks); // start all at 255
        for (int j = 0; j < total_chunks; j++) {
            const ChunkNeighbors *chunkNeighbors = &chunkNeighborss[j];
            // if (chunkNeighbors->length == 0) continue;
            RenderLod *renderLod = &renderLods[j];
            const int3 chunk_position = (&chunkPositions[j])->value;
            const int3 stream_point = find_closest_point(stream_points, stream_points_length, chunk_position);
            const unsigned char camera_distance = get_camera_chunk_distance(stream_point, chunk_position);
            if (renderLod->value != camera_distance || check_chunk_lod(left) || check_chunk_lod(right) || check_chunk_lod(back) || check_chunk_lod(front)) {
                camera_distances[j] = camera_distance;
            }
        }
        // for all chunks that updated LODs, also update meshes
        for (int j = 0; j < total_chunks; j++) {
            const unsigned char camera_distance = camera_distances[j];
            if (camera_distance == 255) continue;
            RenderLod *renderLod = &renderLods[j];
            ChunkLodDirty *chunkLodDirty = &chunkLodDirtys[j];
            ChunkDirty *chunkDirty = &chunkDirtys[j];
            renderLod->value = camera_distance;
            chunkDirty->value = chunk_dirty_state_trigger;
            chunkLodDirty->value = chunk_lod_state_trigger;
        }
        streamDirty->value = 0;
    }
    ecs_iter_fini(&chunks_iterator);
    ecs_iter_fini(&streamers_iter);
} zox_declare_system(TerrainLodSystem)
*/
/*unsigned char is_setting_neighbors = 0;
 f or* (int k = 0; k < chunkNeighbors->length; k++) {
 if (!zox_valid(chunkNeighbors->value[k])) {
     is_setting_neighbors = 1;
     continue;
     }
     }
     if (is_setting_neighbors) {
         // camera_distances[j] = camera_distance;
         // break;
         return;
         }*/

// If it is dirty, it will go through and update Chunk RenderLod's
// todo: shouldn't i iterate each table of t these queries?
// todo: Use ChunkLinks for terrain, and assign indexes to our queries for fastest access
// later check if links to terrain that's updating'
// 1 is Children, use this later, but check if its slower than b bulking it  like atm
// initially get all stream point positions:
//unsigned char did_update_stream_points = 0; later if different system iterators (tables)
// todo: keep a list of stream points in Terrain entity and use those
// todo: find a way to check lod changes, including for neighbors
// const unsigned char old_lod = get_terrain_lod_from_camera_distance(renderLod->value);
// const unsigned char new_lod = get_terrain_lod_from_camera_distance(camera_distance);
// check if needs redrawing - needs to check if neighbors updated too....!
//if (old_lod != new_lod) {
// todo: if this OR neighbor chunks have changed actual Lod! do a check for this
//}
