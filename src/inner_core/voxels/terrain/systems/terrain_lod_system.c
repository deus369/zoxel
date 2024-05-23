// this checcks neighbor chunks and makes sure surrounding ones update too (i think?)
#define check_chunk_lod(dir)\
    (chunkNeighbors->value[direction##_##dir] != 0 &&\
    zox_gett_value(chunkNeighbors->value[direction##_##dir], RenderLod) != \
    get_camera_chunk_distance(stream_point, int3##_##dir(chunk_position)))

// For each terrain, it uses it's Chunks and StreamerLinks (todo)
// If it is dirty, it will go through and update Chunk RenderLod's'
void TerrainLodSystem(ecs_iter_t *it) {
    unsigned char did_do = 0;
    zox_iter_world()
    ctx2 *filters = (ctx2 *) it->ctx;
    ecs_query_t *chunks_query = filters->x;
    ecs_iter_t chunks_iterator = ecs_query_iter(world, chunks_query);
    ecs_query_next(&chunks_iterator);
    int total_chunks = chunks_iterator.count;
    if (total_chunks == 0) return;
    ecs_query_t *streamers_query = filters->y;
    ecs_iter_t streamers_iter = ecs_query_iter(world, streamers_query);
    ecs_query_next(&streamers_iter);
    int total_streamers = streamers_iter.count;
    if (total_streamers == 0) return;
    const int stream_points_length = total_streamers;
    // zox_field_in(ChunkLinks, chunkLinks, 1)
    zox_field_out(StreamDirty, streamDirtys, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(StreamDirty, streamDirtys, streamDirty)
        if (!streamDirty->value) continue;
        streamDirty->value = 0;
        int3 *stream_points = malloc(stream_points_length * sizeof(int3)); // gonna be a problem
        const StreamPoint *streamPoints = ecs_field(&streamers_iter, StreamPoint, 1);
        for (int j = 0; j < total_streamers; j++) {
            const int3 stream_point = (&streamPoints[j])->value;
            stream_points[j] = stream_point;
        }
        unsigned char *chunk_lods = malloc(total_chunks);
        const ChunkPosition *chunkPositions = ecs_field(&chunks_iterator, ChunkPosition, 1);
        const ChunkNeighbors *chunkNeighbors2 = ecs_field(&chunks_iterator, ChunkNeighbors, 2);
        RenderLod *renderLods = ecs_field(&chunks_iterator, RenderLod, 3);
        ChunkDirty *chunkDirtys = ecs_field(&chunks_iterator, ChunkDirty, 4);
        ChunkLodDirty *chunkLodDirtys = ecs_field(&chunks_iterator, ChunkLodDirty, 5);
        for (int j = 0; j < total_chunks; j++) {
            const int3 chunk_position = (&chunkPositions[j])->value;
            const ChunkNeighbors *chunkNeighbors = &chunkNeighbors2[j];
            RenderLod *renderLod = &renderLods[j];
            const int3 stream_point = find_closest_point(stream_points, stream_points_length, chunk_position);
            // zox_log("   + closest %ix%ix%i\n", stream_point.x, stream_point.y, stream_point.z)
            unsigned char camera_distance = get_camera_chunk_distance(stream_point, chunk_position);
            if (renderLod->value != camera_distance || check_chunk_lod(left) || check_chunk_lod(right) || check_chunk_lod(back) || check_chunk_lod(front)) {
                chunk_lods[j] = camera_distance;
            } else {
                chunk_lods[j] = 255;
            }
        }
        for (int j = 0; j < total_chunks; j++) {
            const unsigned char camera_distance = chunk_lods[j];
            if (camera_distance == 255) continue;
            ChunkLodDirty *chunkLodDirty = &chunkLodDirtys[j];
            ChunkDirty *chunkDirty = &chunkDirtys[j];
            RenderLod *renderLod = &renderLods[j];
            // const unsigned char old_lod = get_terrain_lod_from_camera_distance(renderLod->value);
            // const unsigned char new_lod = get_terrain_lod_from_camera_distance(camera_distance);
            renderLod->value = camera_distance;
            // check if needs redrawing - needs to check if neighbors updated too....!
            //if (old_lod != new_lod) {
            // todo: if this OR neighbor chunks have changed actual Lod! do a check for this
            chunkDirty->value = 1;
            chunkLodDirty->value = 1;
            //}
        }
        free(chunk_lods);
        free(stream_points);
        did_do = 1;
    }
    // if (did_do) zox_log(" + terrain chunks lod updated\n")
} zox_declare_system(TerrainLodSystem)

// later check if links to terrain that's updating'
// 1 is Children, use this later, but check if its slower than b bulking it  like atm
// initially get all stream point positions:
//unsigned char did_update_stream_points = 0; later if different system iterators (tables)
// todo: keep a list of stream points in Terrain entity and use those
// zox_log("stream_points: %i\n", stream_points_length)
