// when terrain lod updates, it will update [Block Vox] lods
void ChunkBlocksLodSystem(ecs_iter_t *it) {
#ifdef zox_disable_block_voxes
    return;
#endif
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(RenderLod, renderLods, 2)
    zox_field_in(BlockSpawns, blockSpawnss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_vox_blocks_update) continue;
        zox_field_i(BlockSpawns, blockSpawnss, blockSpawns)
        if (!blockSpawns->value || !blockSpawns->value->data) continue;
        zox_field_i(RenderLod, renderLods, renderLod)
        const unsigned char camera_distance = renderLod->value;
        const unsigned char vox_lod = get_voxes_lod_from_camera_distance(camera_distance);
        for (int j = 0; j < blockSpawns->value->size; j++) {
            const byte3_hashmap_pair* pair = blockSpawns->value->data[j];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                const ecs_entity_t e2 = pair->value;
                if (e2 && zox_valid(e2) && zox_has(e2, RenderLod)) {
                    const unsigned char current_lod = zox_get_value(e2, RenderLod)
                    if (current_lod != vox_lod) {
                        zox_set(e2, RenderLod, { vox_lod })
                        zox_set(e2, ChunkDirty, { chunk_dirty_state_lod_updated })
                    }
                }
                pair = pair->next;
                checks++;
            }
        }
    }
} zox_declare_system(ChunkBlocksLodSystem)
