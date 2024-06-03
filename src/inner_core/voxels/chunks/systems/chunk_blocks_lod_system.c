// when terrain lod updates, it will update character lods
void ChunkBlocksLodSystem(ecs_iter_t *it) {
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(RenderLod, renderLods, 2)
    zox_field_in(BlockSpawns, blockSpawnss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != 2) continue;
        zox_field_i(BlockSpawns, blockSpawnss, blockSpawns)
        if (!blockSpawns->value || !blockSpawns->value->data) continue;
        zox_field_i(RenderLod, renderLods, renderLod)
        const unsigned char vox_lod = get_voxes_lod_from_camera_distance(renderLod->value);
        for (int j = 0; j < blockSpawns->value->size; j++) {
            const byte3_hashmap_pair* pair = blockSpawns->value->data[j];
            while (pair != NULL) {
                const ecs_entity_t e2 = pair->value;
                if (e2 && zox_valid(e2)) {
                    const unsigned char current_lod = zox_get_value(e2, RenderLod)
                    if (current_lod != vox_lod) {
                        zox_set(e2, RenderLod, { vox_lod })
                        zox_set(e2, ChunkDirty, { 1 })
                    }
                }
                pair = pair->next;
            }
        }
    }
} zox_declare_system(ChunkBlocksLodSystem)
