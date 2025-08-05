// should i grab neighbor states instead, or should i create setters?
//  probably grab them, its faster to write in my systems
void Chunk3NeighborsMeshTriggerSystem(ecs_iter_t *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(ChunkNeighbors);
    zox_sys_in(VoxelNodeDirty);
    zox_sys_out(ChunkMeshDirty);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkNeighbors, neighbors);
        zox_sys_i(VoxelNodeDirty, voxelNodeDirty);
        zox_sys_o(ChunkMeshDirty, chunkMeshDirty);
        if (chunkMeshDirty->value != zox_dirty_none || voxelNodeDirty->value != zox_dirty_none) {
            continue;
        }
        byte neighbor_dirty = 0;
        for (byte j = 0; j < chunk_neighbors_length; j++) {
            ecs_entity_t n = neighbors->value[j];
            if (!zox_valid(n) || !zox_has(n, VoxelNodeDirty)) {
                continue;
            }
            zox_geter_value(n, VoxelNodeDirty, byte, state);
            if (state == zox_dirty_active) {
                neighbor_dirty = 1;
                break;
            }
            // zox_set(n, ChunkMeshDirty, { chunk_dirty_state_trigger });
        }
        if (neighbor_dirty) {
            chunkMeshDirty->value = chunk_dirty_state_trigger;
        }
    }
} zox_declare_system(Chunk3NeighborsMeshTriggerSystem)