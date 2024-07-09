/*void ChunkEntitiesTriggerSystem(ecs_iter_t *it) {
    unsigned char did_do = 0;
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_out(GenerateChunkEntities, generateChunkEntitiess, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (!chunkLodDirty->value) continue;
        zox_field_o(GenerateChunkEntities, generateChunkEntitiess, generateChunkEntities)
        generateChunkEntities->value = 1;
        did_do = 1;
    }
    // if (did_do) zox_log("   + chunk entities lods updating\n")
} zox_declare_system(ChunkEntitiesTriggerSystem)
*/
