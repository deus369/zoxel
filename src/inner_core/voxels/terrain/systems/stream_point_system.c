#define check_chunk_lod(dir)\
    (chunkNeighbors->value[direction##_##dir] != 0 &&\
    ecs_get(world, chunkNeighbors->value[direction##_##dir], RenderLod)->value != \
    get_chunk_division(new_position, int3##_##dir(chunkPosition->value)))

void StreamPointSystem(ecs_iter_t *it) {
    #ifdef voxels_disable_streaming
        return;
    #endif
    ecs_world_t *world = it->world;
    ecs_query_t *chunks_query = it->ctx;
    ecs_iter_t chunks_iterator = ecs_query_iter(world, chunks_query);
    ecs_query_next(&chunks_iterator);
    int total_chunks = chunks_iterator.count;
    if (total_chunks == 0) return;
    #ifdef zoxel_time_stream_point_system
        begin_timing()
    #endif
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    StreamPoint *streamPoints = ecs_field(it, StreamPoint, 3);
    const ChunkPosition *chunkPositions = ecs_field(&chunks_iterator, ChunkPosition, 2);
    const ChunkNeighbors *chunkNeighbors2 = ecs_field(&chunks_iterator, ChunkNeighbors, 3);
    RenderLod *renderLods = ecs_field(&chunks_iterator, RenderLod, 4);
    ChunkDirty *chunkDirtys = ecs_field(&chunks_iterator, ChunkDirty, 5);
    for (int i = 0; i < it->count; i++) {
        const Position3D *position3D = &position3Ds[i];
        int3 new_position = get_chunk_position(position3D->value, default_chunk_size);  // translate position to int3 chunk position
        // printf("Checking Streamer position3D: [%fx%fx%f] \n", position3D->value.x, position3D->value.y, position3D->value.z);
        StreamPoint *streamPoint = &streamPoints[i];
        if (!int3_equals(new_position, streamPoint->value)) {
            streamPoint->value = new_position;
            // zoxel_log(" > stream terrain from [%lu] at [%ix%ix%i]\n", it->entities[i], new_position.x, new_position.y, new_position.z);
            // did_update = 1;
            #ifdef zoxel_time_stream_point_system
                int updated_count = 0;
            #endif
            unsigned char *changed = malloc(total_chunks);
            for (int j = 0; j < total_chunks; j++) {
                // todo: check terrain matches up to stream points
                const ChunkPosition *chunkPosition = &chunkPositions[j];
                unsigned char new_chunk_division = get_chunk_division(new_position, chunkPosition->value);
                RenderLod *renderLod = &renderLods[j];
                const ChunkNeighbors *chunkNeighbors = &chunkNeighbors2[j];
                if (renderLod->value != new_chunk_division || check_chunk_lod(left) || check_chunk_lod(right) || check_chunk_lod(back) || check_chunk_lod(front)) {
                    changed[j] = new_chunk_division;
                    #ifdef zoxel_time_stream_point_system
                        updated_count++;
                    #endif
                } else {
                    changed[j] = 255;
                }
            }
            for (int j = 0; j < total_chunks; j++) {
                const unsigned char changed_chunk = changed[j];
                if (changed_chunk == 255) continue;
                RenderLod *renderLod = &renderLods[j];
                ChunkDirty *chunkDirty = &chunkDirtys[j];
                renderLod->value = changed_chunk;
                chunkDirty->value = 1;
            }
            free(changed);
            #ifdef zoxel_time_stream_point_system
                did_do_timing()
                zoxel_log(" > stream point updated [%i / %i]\n", updated_count, total_chunks);
            #endif
        }
    }
    //if (!did_update) ecs_query_skip(it); // skip table updates here if no updates
    #ifdef zoxel_time_stream_point_system
        end_timing("StreamPointSystem")
    #endif
} zox_declare_system(StreamPointSystem)