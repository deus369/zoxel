// refresh mesh if neighbor updates
// is this still used
void ChunkNeighborUpdatedSystem(ecs_iter_t *it) {
    /*zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkNeighbors)
    zox_sys_out(ChunkMeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ChunkMeshDirty, chunkMeshDirty)
        zox_sys_i(ChunkNeighbors, chunkNeighbors)
        for (int k = 0; k < chunk_neighbors_length; k++) {
            const ecs_entity_t n = chunkNeighbors->value[k];
            if (!zox_valid(n) || !zox_has(n, ChunkLodDirty)) {
                continue;
            }
            zox_geter_value(n, ChunkLodDirty, neighborChunkLodDirty, byte, state)
            if (state == chunk_lod_state_mesh_trigger) {
                chunkMeshDirty->value = chunk_dirty_state_trigger;
                break;
            }
        }
    }*/
} zox_declare_system(ChunkNeighborUpdatedSystem)