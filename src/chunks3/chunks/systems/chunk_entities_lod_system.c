// chunk_lod_state_characters_update :: when terrain lod updates, update character lods
void ChunkEntitiesLodSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkLodDirty)
    zox_sys_in(RenderDistance)
    zox_sys_in(EntityLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkLodDirty, chunkLodDirty)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(EntityLinks, entityLinks)
        if (chunkLodDirty->value != chunk_lod_state_characters_update) {
            // continue;
        }
        for (int j = 0; j < entityLinks->length; j++) {
            const ecs_entity_t e2 = entityLinks->value[j];
            if (!(e2 && zox_valid(e2) && zox_has(e2, RenderLod))) {
                continue;
            }
            zox_geter_value(e2, RenderLod, byte, current_lod)
            zox_geter_value(e2, NodeDepth, byte, node_depth)
            const byte new_lod = distance_to_lod_npc(renderDistance->value);
            if (current_lod == new_lod) {
                continue;  // check if characters division
            }
            zox_set(e2, RenderLod, { new_lod })
            zox_set(e2, ChunkMeshDirty, { chunk_dirty_state_trigger })
        }
    }
} zox_declare_system(ChunkEntitiesLodSystem)
