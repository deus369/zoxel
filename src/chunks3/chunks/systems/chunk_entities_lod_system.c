// chunk_lod_state_characters_update :: when terrain lod updates, update character lods
void ChunkEntitiesLodSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(RenderDistance)
    zox_sys_in(EntityLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(EntityLinks, entityLinks)
        if (renderDistanceDirty->value != zox_dirty_active) {
            continue;
        }
        for (int j = 0; j < entityLinks->length; j++) {
            const ecs_entity_t e2 = entityLinks->value[j];
            if (!(e2 && zox_valid(e2) && zox_has(e2, RenderLod))) {
                continue;
            }
            zox_geter_value(e2, RenderLod, byte, current_lod)
            // zox_geter_value(e2, NodeDepth, byte, node_depth)
            const byte new_lod = distance_to_lod_npc(renderDistance->value);
            if (current_lod == new_lod) {
                continue;  // check if characters division
            }
            // zox_log("[%s] is now dirty [%i]", zox_get_name(e2), new_lod)
            zox_set(e2, RenderLod, { new_lod })
            zox_set(e2, RenderLodDirty, { zox_dirty_trigger })
        }
    }
} zox_declare_system(ChunkEntitiesLodSystem)
