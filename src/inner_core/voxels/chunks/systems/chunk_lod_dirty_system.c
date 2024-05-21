/*void ChunkLodDirtySystem(ecs_iter_t *it) {
    zox_field_in(ChunkDirty, chunkDirtys, 1)
    zox_field_out(ChunkLodDirty, chunkLodDirtys, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ChunkDirty, chunkDirtys, chunkDirty)
        if (!chunkDirty->value) continue;
        zox_field_i_out(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        chunkLodDirty->value = 1;
    }
} zox_declare_system(ChunkLodDirtySystem)
*/
