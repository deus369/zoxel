void NoiseChunkOctreeSystem(ecs_iter_t *it) {
    zox_change_check()
    const byte max_depth = max_octree_depth;
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
        byte chunk_depth = get_chunk_division_from_lod(renderLod->value, max_depth);
        random_fill_octree(chunkOctree, 1, chunk_depth);
#ifndef zox_disable_closing_octree_nodes
        close_solid_nodes(chunkOctree, max_octree_depth);
#endif
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }
} zox_declare_system(NoiseChunkOctreeSystem)