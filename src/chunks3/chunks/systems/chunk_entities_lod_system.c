// chunk_lod_state_characters_update :: when terrain lod updates, update character lods
void ChunkEntitiesLodSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(RenderDistance, renderDistances, 2)
    zox_field_in(EntityLinks, entityLinkss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_characters_update) continue;
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        const byte new_lod = get_voxes_lod_from_camera_distance(renderDistance->value);
        zox_field_i(EntityLinks, entityLinkss, entityLinks)
        for (int j = 0; j < entityLinks->length; j++) {
            const ecs_entity_t e2 = entityLinks->value[j];
            if (!(e2 && zox_valid(e2) && zox_has(e2, RenderLod))) continue;
            const byte current_lod = zox_get_value(e2, RenderLod)
            if (current_lod == new_lod) continue;  // check if characters division
            zox_set(e2, RenderLod, { new_lod })
            zox_set(e2, ChunkMeshDirty, { chunk_dirty_state_trigger })
        }
    }
} zox_declare_system(ChunkEntitiesLodSystem)
