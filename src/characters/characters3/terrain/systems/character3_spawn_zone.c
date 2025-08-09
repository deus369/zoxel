void Characters3SpawnZoneSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(RenderDistance)
    zox_sys_out(CharacterSpawnZone)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_o(CharacterSpawnZone, characterSpawnZone)
        // update when dirty
        if (renderDistanceDirty->value == zox_dirty_active) {
            characterSpawnZone->value = renderDistance->value <= terrain_lod_near;
        }
    }
} zoxd_system(Characters3SpawnZoneSystem)