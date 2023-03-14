void StreamPointSystem(ecs_iter_t *it)
{
    #ifdef voxels_disable_streaming
        return;
    #endif
    unsigned char did_update = 0;
    const int3 chunk_size = (int3) { 16, 16, 16 };
    ecs_query_t *chunks_query = it->ctx;
    ecs_iter_t chunks_iterator = ecs_query_iter(it->world, chunks_query);
    ecs_query_next(&chunks_iterator);
    int total_chunks = chunks_iterator.count;
    if (total_chunks == 0)
    {
        return;
    }
    #ifdef zoxel_time_stream_point_system
        begin_timing()
    #endif
    const ChunkPosition *chunkPositions = ecs_field(&chunks_iterator, ChunkPosition, 2);
    const ChunkNeighbors *chunkNeighbors2 = ecs_field(&chunks_iterator, ChunkNeighbors, 3);
    ChunkDivision *chunkDivisions = ecs_field(&chunks_iterator, ChunkDivision, 4);
    ChunkDirty *chunkDirtys = ecs_field(&chunks_iterator, ChunkDirty, 5);
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    StreamPoint *streamPoints = ecs_field(it, StreamPoint, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Position3D *position3D = &position3Ds[i];
        int3 new_position = get_chunk_position(position3D->value, chunk_size);  // translate position to int3 chunk position
        // printf("Checking Streamer position3D: [%fx%fx%f] \n", position3D->value.x, position3D->value.y, position3D->value.z);
        StreamPoint *streamPoint = &streamPoints[i];
        if (!int3_equal(new_position, streamPoint->value))
        {
            streamPoint->value = new_position;
            did_update = 1;
            #ifdef zoxel_time_stream_point_system
                int updated_count = 0;
            #endif
            unsigned char *changed = malloc(total_chunks);
            for (int j = 0; j < total_chunks; j++)
            {
                // later check matching world
                const ChunkPosition *chunkPosition = &chunkPositions[j];
                unsigned char new_chunk_division = get_chunk_division(new_position, chunkPosition->value);
                ChunkDivision *chunkDivision = &chunkDivisions[j];
                const ChunkNeighbors *chunkNeighbors = &chunkNeighbors2[j];
                if (chunkDivision->value != new_chunk_division ||
                    // check if neighbors changed division
                    (chunkNeighbors->value[0] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[0], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_left(chunkPosition->value))) ||
                    (chunkNeighbors->value[1] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[1], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_right(chunkPosition->value))) ||
                    (chunkNeighbors->value[4] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[4], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_back(chunkPosition->value)))  ||
                    (chunkNeighbors->value[5] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[5], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_front(chunkPosition->value))))
                {
                    changed[j] = new_chunk_division;
                    #ifdef zoxel_time_stream_point_system
                        updated_count++;
                    #endif
                }
                else
                {
                    changed[j] = 255;
                }
            }
            for (int j = 0; j < total_chunks; j++)
            {
                if (changed[j] != 255)
                {
                    ChunkDivision *chunkDivision = &chunkDivisions[j];
                    ChunkDirty *chunkDirty = &chunkDirtys[j];
                    chunkDivision->value = changed[j];
                    chunkDirty->value = 1;
                }
            }
            free(changed);
            #ifdef zoxel_time_stream_point_system
                did_do_timing()
                zoxel_log(" > stream point updated [%i / %i]\n", updated_count, total_chunks);
            #endif
        }
    }
    // skip table updates here if no updates
    if (!did_update)
    {
        // ecs_query_skip(it);
    }
    #ifdef zoxel_time_stream_point_system
        end_timing("StreamPointSystem")
    #endif
}
zoxel_declare_system(StreamPointSystem)

/*ecs_query_t *changeQuery = it->ctx;
ecs_iter_t change_iter = ecs_query_iter(it->world, changeQuery);
while (ecs_query_next(&change_iter))
{
    if (change_iter.table != it->table)
    {
        ecs_query_skip(&change_iter);
    }
}
if (!ecs_query_changed(NULL, &change_iter))
{
    printf("Position3D has not changed.\n");
    return;
}*/
//! todo only check when Position3D changes.
/*if (!ecs_query_changed(NULL, it))
{
    // printf("Position3D has not changed.\n");
    return;
}*/
// printf("StreamPointSystem Updated\n");
/*if (!ecs_query_changed(it->ctx, NULL))
{
    printf("Position3D has not changed.\n");
    return;
}*/
            // printf("Stream Point Updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            // update chunk divisions
            /*ecs_entity_t terrain_world = ecs_get(it->world, it->entities[i], VoxLink)->value;
            const ChunkLinks *chunkLinks = ecs_get(it->world, terrain_world, ChunkLinks);
            for (int j = 0; j < chunkLinks->length; j++)
            {
                ecs_entity_t chunk_entity = chunkLinks->value[j];
                const ChunkPosition *chunkPosition = ecs_get(it->world, chunk_entity, ChunkPosition);
                unsigned char new_chunk_division = get_chunk_division(new_position, chunkPosition->value);
                const ChunkDivision *chunkDivision = ecs_get(it->world, chunk_entity, ChunkDivision);
                const ChunkNeighbors *chunkNeighbors = ecs_get(it->world, chunk_entity, ChunkNeighbors);
                if (chunkDivision->value != new_chunk_division ||
                    // check if neighbors changed division
                    (chunkNeighbors->value[5] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[5], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_front(chunkPosition->value))) ||
                    (chunkNeighbors->value[4] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[4], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_back(chunkPosition->value))) ||
                    (chunkNeighbors->value[0] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[0], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_left(chunkPosition->value))) ||
                    (chunkNeighbors->value[1] != 0 && 
                        ecs_get(it->world, chunkNeighbors->value[1], ChunkDivision)->value !=
                        get_chunk_division(new_position, int3_right(chunkPosition->value)))
                        )
                {
                    ecs_set(it->world, chunk_entity, ChunkDivision,
                        { new_chunk_division });
                    ecs_set(it->world, chunk_entity, ChunkDirty, { 1 });
                }
            }
            // printf("    > Resetting Chunks [%i]\n", chunkLinks->length);*/