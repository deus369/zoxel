void ChunkLodDirtySystem(ecs_iter_t *it) {
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(RenderLod, renderLods, 2)
    zox_field_out(GenerateChunk, generateChunks, 3)
    zox_field_out(ChunkMeshDirty, chunkMeshDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        zox_field_i(RenderLod, renderLods, renderLod)
        if (chunkLodDirty->value == chunk_lod_state_generate_trigger) {
            zox_field_o(GenerateChunk, generateChunks, generateChunk)
            generateChunk->value = 1;
        } else if (chunkLodDirty->value == chunk_lod_state_mesh_trigger) {
            if (renderLod->value != render_lod_invisible) {
                zox_field_o(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
                chunkMeshDirty->value = chunk_dirty_state_trigger;
            }
        }
    }
} zox_declare_system(ChunkLodDirtySystem)