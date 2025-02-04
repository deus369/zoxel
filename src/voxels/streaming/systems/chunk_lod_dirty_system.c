void ChunkLodDirtySystem(ecs_iter_t *it) {
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkNeighbors, chunkNeighborss, 2)
    zox_field_out(GenerateChunk, generateChunks, 3)
    zox_field_out(ChunkMeshDirty, chunkMeshDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value == chunk_lod_state_generate_trigger) {
            zox_field_o(GenerateChunk, generateChunks, generateChunk)
            generateChunk->value = 1;
        } else if (chunkLodDirty->value == chunk_lod_state_mesh_trigger) {
            if (zox_gett_value(it->entities[i], RenderLod) != render_lod_invisible) {
                zox_field_o(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
                chunkMeshDirty->value = chunk_dirty_state_trigger;
                zox_field_i(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
                for (int k = 0; k < chunkNeighbors->length; k++) {
                    const ecs_entity_t neighbor = chunkNeighbors->value[k];
                    // if (!zox_valid(neighbor)) zox_log("AEWIJOWAE\n")
                    if (!zox_valid(neighbor)) continue;
                    zox_set(neighbor, ChunkMeshDirty, { chunk_dirty_state_trigger })
                }
            }
        }
    }
} zox_declare_system(ChunkLodDirtySystem)
