// chunk_lod_state_characters_update :: when terrain lod updates, update character lods
void ChunkEntitiesLodSystem(iter *it) {
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
        const byte new_lod = distance_to_lod_npc(renderDistance->value);
        for (int j = 0; j < entityLinks->length; j++) {
            const entity e2 = entityLinks->value[j];
            if (!(e2 && zox_valid(e2) && zox_has(e2, RenderLod))) {
                continue;
            }
            zox_geter_value(e2, RenderLod, byte, old_lod)
            if (old_lod != new_lod) {
                // zox_log("[%s] is now dirty [%i]", zox_get_name(e2), new_lod)
                zox_set(e2, RenderLod, { new_lod })
                zox_set(e2, RenderLodDirty, { zox_dirty_trigger })
            }
        }
    }
} zox_declare_system(ChunkEntitiesLodSystem)
