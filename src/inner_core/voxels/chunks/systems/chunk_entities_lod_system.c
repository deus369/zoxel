// when terrain lod updates, it will update character lods
void ChunkEntitiesLodSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(RenderLod, renderLods, 2)
    zox_field_in(EntityLinks, entityLinkss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_characters_update) continue;
        zox_field_i(RenderLod, renderLods, renderLod)
        const unsigned char new_lod = get_voxes_lod_from_camera_distance(renderLod->value);
        zox_field_i(EntityLinks, entityLinkss, entityLinks)
        for (int j = 0; j < entityLinks->length; j++) {
            const ecs_entity_t e2 = entityLinks->value[j];
            if (!(e2 && zox_valid(e2) && zox_has(e2, RenderLod))) continue;
            const unsigned char current_lod = zox_get_value(e2, RenderLod)
            if (current_lod == new_lod) continue;  // check if characters division
            zox_set(e2, RenderLod, { new_lod })
            zox_set(e2, ChunkDirty, { chunk_dirty_state_generated })
        }
    }
} zox_declare_system(ChunkEntitiesLodSystem)
