void NoiseChunkOctreeSystem(ecs_iter_t *it) {
    const byte max_depth = terrain_depth;
    zox_change_check()
    zox_field_world()
    zox_field_in(RenderLod, renderLods, 4)
    zox_field_out(ChunkDirty, chunkDirtys, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(GenerateChunk, generateChunks, 5)
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
        close_solid_nodes(world, chunkOctree, chunkOctree->linked);
#endif
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }
} zox_declare_system(NoiseChunkOctreeSystem)