// updates during ChunkDirty step, also checks render disabled
// When we destroy block vox, update, or when we place
void BlockVoxUpdateSystem(ecs_iter_t *it) {
#if defined(zox_disable_block_voxes) || defined(zox_disable_block_voxes2)
    return;
#endif
    zox_field_in(ChunkDirty, chunkDirtys, 1)
    zox_field_in(BlocksSpawned, blocksSpawneds, 2)
    zox_field_out(ChunkLodDirty, chunkLodDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value == chunk_dirty_state_none) continue; // != chunk_dirty_state_edited) continue;
        zox_field_i(BlocksSpawned, blocksSpawneds, blocksSpawned)
        if (!blocksSpawned->value) continue;
        zox_field_o(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        const unsigned char chunk_lod_dirty = chunkLodDirty->value; //  zox_get_value(e, ChunkLodDirty)
        if (chunk_lod_dirty == 0 || chunk_lod_dirty > chunk_lod_state_vox_blocks_spawn) {
            chunkLodDirty->value = chunk_lod_state_vox_blocks_spawn;
            // zox_set(e, ChunkLodDirty, { chunk_lod_state_vox_blocks_spawn })
        }
    }
} zox_declare_system(BlockVoxUpdateSystem)
