//! Our function that creates a chunk.
void GenerateOctreeChunkTerrain(ChunkOctree* chunkOctree, const int3 chunkSize, const int3 chunkPosition)
{
    //  int3 node_size = (int3) { 2, 2, 2 };
    int3 local_position;
    for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++)
            {
                int array_index = int3_array_index(local_position, octree_node_size3);
                // chunkOctree->nodes[array_index].value = 1;
                if (local_position.y == 1 && local_position.x == 1 && local_position.z == 1)
                {
                    chunkOctree->nodes[array_index].value = 1;
                    open_ChunkOctree(&chunkOctree->nodes[array_index]);
                    for (int i = 0; i < octree_length; i++)
                    {
                        chunkOctree->nodes[array_index].nodes[i].value = rand() % 2;
                    }
                }
                else if (local_position.y == 0 || rand() % 100 >= 60)
                {
                    chunkOctree->nodes[array_index].value = 1;
                }
            }
        }
    }
}

void OctreeTerrainChunkSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 4);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 5);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 6);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 0)
        {
            continue;
        }
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0)
        {
            continue;
        }
        chunkDirty->value = 1;
        ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        // open first node
        open_ChunkOctree(chunkOctree);
        GenerateOctreeChunkTerrain(chunkOctree, chunkSize->value, chunkPosition->value);
        // printf("Terrain ChunkData Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(OctreeTerrainChunkSystem)

    /*for (int i = 0; i < 4; i++)
    {
        chunkOctree->nodes[i].value = 1;
    }
    for (int i = 0; i < 4; i++)
    {
        if (rand() % 100 >= 60)
        {
            chunkOctree->nodes[4 + i].value = 1;
        }
    }*/
    // srand(666);
    /*int3 local_position;
    int3 global_position;
    int3 chunk_position_offset = voxel_chunk_position_xz(chunkPosition, chunkSize);
    for (local_position.x = 0; local_position.x < chunkSize.x; local_position.x++)
    {
        for (local_position.z = 0; local_position.z < chunkSize.z; local_position.z++)
        {
            local_position.y = 0;
            global_position = int3_add(local_position, chunk_position_offset);
            // printf("global_position [%ix%ix%i]\n", global_position.x, global_position.y, global_position.z);
            // printf("global_position: [%fx%fx%f]\n", global_position.x, global_position.y, global_position.z);
            float2 noise_point = float2_from_int2((int2) { global_position.x, global_position.z });
            noise_point.x += 3200;
            noise_point.y += 3200;
            int terrain_height2 = terrain_min_height +
                // int_floor(terrain_amplifier * simplex_fun_2D(noise_point, terrain_frequency));
                // int_floor(terrain_amplifier * perlin_noise(noise_point.x, noise_point.y, terrain_frequency, seed));
                int_floor(terrain_amplifier * perlin_terrain(noise_point.x, noise_point.y,
                    terrain_frequency, terrain_seed, terrain_octaves));
                // int_floor(terrain_amplifier * generate_noise_2D(noise_point, terrain_frequency));
            if (terrain_height2 < terrain_min_height)
            {
                terrain_height2 = terrain_min_height;
            }
            // unsigned char terrain_height2 = terrain_height + rand() % terrain_height_amplifier;
            for (local_position.y = 0; local_position.y < chunkSize.y; local_position.y++)
            {
                int array_index = int3_array_index(local_position, chunkSize);
                if (local_position.y <= terrain_height2)
                {
                    chunk->value[array_index] = 1;
                }
                else
                {
                    chunk->value[array_index] = 0;
                }
                // valueRange.x + rand() % (valueRange.y - valueRange.x);
                // array_index++;
            }
        }
    }*/