void NoiseVoxelNodeSystem(iter *it) {
    // const byte max_depth = terrain_depth;
    zox_change_check()
    zox_sys_begin()
    zox_sys_in(NodeDepth)
    zox_sys_out(ChunkDirty)
    zox_sys_out(VoxelNode)
    zox_sys_out(GenerateChunk)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_o(ChunkDirty, chunkDirty)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(GenerateChunk, generateChunk)
        if (!generateChunk->value || chunkDirty->value) {
            continue;
        }
        random_fill_octree(voxelNode, 1, nodeDepth->value);
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }
} zoxd_system(NoiseVoxelNodeSystem)