// refresh mesh if neighbor updates
void ChunkNeighborUpdatedSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ChunkNeighbors, chunkNeighborss, 1)
    zox_field_out(ChunkMeshDirty, chunkMeshDirtys, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
        zox_field_i(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
        for (int k = 0; k < chunk_neighbors_length; k++) {
            const ecs_entity_t neighbor = chunkNeighbors->value[k];
            if (zox_valid(neighbor)) {
                zox_geter(neighbor, ChunkLodDirty, neighborChunkLodDirty)
                if (neighborChunkLodDirty->value == chunk_lod_state_mesh_trigger) {
                    chunkMeshDirty->value = chunk_dirty_state_trigger;
                    break;
                }
            }
        }
    }
} zox_declare_system(ChunkNeighborUpdatedSystem)