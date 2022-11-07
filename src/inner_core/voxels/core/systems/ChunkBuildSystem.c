// set_mesh_indicies(world, e, cubeIndicies, 36);
// set_mesh_vertices(world, e, cubeVertices, 24);

//! Builds a mesh data from the chunk!
void ChunkBuildSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    const EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    const Chunk *chunks = ecs_field(it, Chunk, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 5);
    for (int i = 0; i < it->count; i++)
    {
        const EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value == 0)
        {
            continue;
        }
        printf("Building Chunk Mesh [%lu]\n", (long int) it->entities[i]);
        const Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        // go through and add a top face for each voxel position that is solid
        int index = 0;
        for (int j = 0; j < chunkSize->value.x; j++)
        {
            for (int k = 0; k < chunkSize->value.y; k++)
            {
                for (int l = 0; l < chunkSize->value.y; l++)
                {
                    if (chunk->value[index] != 0)
                    {
                        // add faces! based on neighbors
                    }
                    index++;
                }
            }
        }
        // invalid free?
        // set_mesh_indicies(&meshIndicies2, cubeIndicies, 36);
        // set_mesh_vertices(&meshVertices2, cubeVertices, 24);
        // list?
        // re_initialize_memory_component(chunk, unsigned char, chunkSize->value.x * chunkSize->value.y * chunkSize->value.z);
        /// GenerateChunkNoise(chunk, chunkSize);
    }
}
ECS_SYSTEM_DECLARE(ChunkBuildSystem);