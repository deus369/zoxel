// should i grab neighbor states instead, or should i create setters?
//  probably grab them, its faster to write in my systems

// When: VoxelNodeDirty is zox_dirty_active
void Chunk3MeshTriggerSystem(ecs_iter_t *it) {
    zox_sys_begin();
    zox_sys_in(VoxelNodeDirty);
    zox_sys_out(ChunkMeshDirty);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxelNodeDirty, voxelNodeDirty);
        zox_sys_o(ChunkMeshDirty, chunkMeshDirty);
        if (chunkMeshDirty->value == zox_dirty_none && voxelNodeDirty->value == zox_dirty_active) {
            chunkMeshDirty->value = chunk_dirty_state_trigger;
        }
    }
} zox_declare_system(Chunk3MeshTriggerSystem)