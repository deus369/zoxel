void ChunkLodDirtySystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ChunkLodDirty)
    zox_sys_in(RenderLod)
    zox_sys_out(GenerateChunk)
    zox_sys_out(ChunkMeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkLodDirty, chunkLodDirty)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_o(GenerateChunk, generateChunk)
        zox_sys_o(ChunkMeshDirty, chunkMeshDirty)
        if (chunkLodDirty->value == chunk_lod_state_generate_trigger) {
            generateChunk->value = 1;
        } /*else if (chunkLodDirty->value == chunk_lod_state_mesh_trigger) {
            if (renderLod->value != render_lod_invisible) {
                chunkMeshDirty->value = chunk_dirty_state_trigger;
            }
        }*/
    }
} zox_declare_system(ChunkLodDirtySystem)