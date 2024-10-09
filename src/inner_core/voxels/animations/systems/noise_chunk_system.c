/*void generate_chunk_noise(ChunkData* chunkData, const ChunkSize *chunkSize) {
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
}*/

/*void NoiseChunkSystem(ecs_iter_t *it) {
    return;
    zox_change_check()
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkData *chunks = ecs_field(it, ChunkData, 3);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 4);
    GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 5);
    for (int i = 0; i < it->count; i++) {
        GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 0) continue;
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        // if (chunkDirty->value != 0) continue;
        const ChunkSize *chunkSize = &chunkSizes[i];
        ChunkData *chunkData = &chunks[i];
        int voxels_array_size = chunkSize->value.x * chunkSize->value.y * chunkSize->value.z;
        resize_memory_component(ChunkData, chunkData, unsigned char, voxels_array_size);
        generate_chunk_noise(chunkData, chunkSize);
        generateChunk->value = 0;
        chunkDirty->value = chunk_dirty_state_generated;
    }
}
zox_declare_system(NoiseChunkSystem)*/

void NoiseChunkOctreeSystem(ecs_iter_t *it) {
    zox_change_check()
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 4);
    GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 5);
    for (int i = 0; i < it->count; i++) {
        GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 0) continue;
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0) continue;
        const RenderLod *renderLod = &renderLods[i];
        ChunkOctree *chunkOctree = &chunkOctrees[i];
        unsigned char chunk_depth = colors_get_max_depth_from_division(renderLod->value); // 5
        random_fill_octree(chunkOctree, 1, chunk_depth);
#ifndef zox_disable_closing_octree_nodes
        close_solid_nodes(chunkOctree);
#endif
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }
} zox_declare_system(NoiseChunkOctreeSystem)
