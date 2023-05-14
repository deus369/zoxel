void generate_chunk_noise(ChunkData* chunkData, const ChunkSize *chunkSize) {
    // zoxel_log("     = [%i]\n", chunkSize->value.x);
    int voxels_count = 0;
    int array_index = 0;
    for (int j = 0; j < chunkSize->value.x; j++) {
        for (int k = 0; k < chunkSize->value.y; k++) {
            for (int l = 0; l < chunkSize->value.z; l++) {
                // int array_index = (j + k * chunkSize->value.x)  * chunkSize->value.y + l;
                int distanceToMidX = abs_integer(chunkSize->value.x / 2 - j);
                int distanceToMidY = abs_integer(chunkSize->value.y / 2 - k);
                int distanceToMidZ = abs_integer(chunkSize->value.z / 2 - l);
                if (distanceToMidX + distanceToMidY >= chunkSize->value.x / 2
                    || distanceToMidX + distanceToMidZ >= chunkSize->value.x / 2
                    || distanceToMidZ + distanceToMidY >= chunkSize->value.x / 2) {
                    chunkData->value[array_index] = 0;
                    array_index++;
                    continue;
                }
                if (rand() % 100 <= dissapearChance) {
                    chunkData->value[array_index] = 0;
                    array_index++;
                    continue;
                }
                chunkData->value[array_index] = 1;
                array_index++;
                voxels_count++;
            }
        }
    }
    // zoxel_log("     + voxels [%i]\n", voxels_count);
}

void NoiseChunkSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkData *chunks = ecs_field(it, ChunkData, 3);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 4);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 5);
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        //! Only rebuild if GenerateChunk is set to 1 and EntityDirty is false.
        if (generateChunk->value == 0) continue;
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0) continue;
        const ChunkSize *chunkSize = &chunkSizes[i];
        ChunkData *chunk = &chunks[i];
        int voxels_array_size = chunkSize->value.x * chunkSize->value.y * chunkSize->value.z;
        re_initialize_memory_component(chunk, unsigned char, voxels_array_size);
        generate_chunk_noise(chunk, chunkSize);
        chunkDirty->value = 1;
        // zoxel_log(" > chunk [noise] generated [%lu] at [%f]\n", it->entities[i], get_total_time_seconds());
    }
}
zox_declare_system(NoiseChunkSystem)

void NoiseChunkOctreeSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const ChunkDivision *chunkDivisions = ecs_field(it, ChunkDivision, 4);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 5);
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        //! Only rebuild if GenerateChunk is set to 1 and EntityDirty is false
        if (generateChunk->value == 0) continue;
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0) continue;
        const ChunkDivision *chunkDivision = &chunkDivisions[i];
        ChunkOctree *chunkOctree = &chunkOctrees[i];
        unsigned char chunk_depth = colors_get_max_depth_from_division(chunkDivision->value); // 5
        random_fill_octree(chunkOctree, 1, chunk_depth);
        #ifdef voxels_close_octree_nodes
            close_solid_nodes(chunkOctree);
        #endif
        chunkDirty->value = 1;
        // zoxel_log(" > chunk octree [noise] generated [%lu] at [%f]\n", it->entities[i], get_total_time_seconds());
    }
}
zox_declare_system(NoiseChunkOctreeSystem)