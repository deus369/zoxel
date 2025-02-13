// updates during ChunkDirty step, also checks render disabled
// When we destroy block vox, update, or when we place
void BlockVoxUpdateSystem(ecs_iter_t *it) {
    /*if (disable_block_voxes) return;
    zox_field_in(ChunkDirty, chunkDirtys, 1)
    zox_field_in(BlocksSpawned, blocksSpawneds, 2)
    zox_field_out(ChunkLodDirty, chunkLodDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value != chunk_dirty_state_update) continue;
        zox_field_i(BlocksSpawned, blocksSpawneds, blocksSpawned)
        if (!blocksSpawned->value) continue;
        zox_field_o(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        const byte chunk_lod_dirty = chunkLodDirty->value; //  zox_get_value(e, ChunkLodDirty)
        if (chunk_lod_dirty == chunk_lod_state_none || chunk_lod_dirty > chunk_lod_state_vox_blocks_spawn) {
            chunkLodDirty->value = chunk_lod_state_vox_blocks_pre_spawn;
        }
    }*/
} zox_declare_system(BlockVoxUpdateSystem)
