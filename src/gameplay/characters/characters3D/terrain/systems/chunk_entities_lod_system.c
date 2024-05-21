// when terrain lod updates, it will update character lods
void ChunkEntitiesLodSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(RenderLod, renderLods, 1)
    zox_field_in(EntityLinks, entityLinkss, 2)
    zox_field_in(BlockSpawns, blockSpawnss, 3)
    zox_field_out(ChunkLodDirty, chunkLodDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value == 0) continue;
        else if (chunkLodDirty->value == 1) {
            chunkLodDirty->value = 2;
            continue;
        }
        chunkLodDirty->value = 0;
        // if (generateChunkEntities->value != zox_chunk_entities_state_spawned) continue;
        zox_field_i_in(RenderLod, renderLods, renderLod)
        const unsigned char camera_distance = renderLod->value;
        const unsigned char new_lod = get_character_division_from_camera(camera_distance);
        zox_field_i_in(EntityLinks, entityLinkss, entityLinks)
        for (int j = 0; j < entityLinks->length; j++) {
            const ecs_entity_t e2 = entityLinks->value[j];
            if (!e2) continue;
            const unsigned char current_lod = zox_get_value(e2, RenderLod)
            if (current_lod == new_lod) continue;  // check if characters division
            zox_set(e2, RenderLod, { new_lod })
            zox_set(e2, ChunkDirty, { 1 })
        }
        zox_field_i_in(BlockSpawns, blockSpawnss, blockSpawns)
        if (blockSpawns->value) {
            for (int j = 0; j < blockSpawns->value->size; j++) {
                const byte3_hash_map_pair* pair = blockSpawns->value->data[j];
                while (pair != NULL) {
                    const ecs_entity_t e2 = pair->value;
                    if (e2 && zox_valid(e2)) {
                        const unsigned char current_lod = zox_get_value(e2, RenderLod)
                        if (current_lod != new_lod) {
                            zox_set(e2, RenderLod, { new_lod })
                            zox_set(e2, ChunkDirty, { 1 })
                        }
                    }
                    pair = pair->next;
                }
            }
        }
    }
} zox_declare_system(ChunkEntitiesLodSystem)
