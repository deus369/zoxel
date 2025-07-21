void Characters3DespawnSystem(ecs_iter_t *it) {
    if (disable_npcs) {
        return;
    }
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(RenderDistance)
    zox_sys_out(CharactersSpawned)
    zox_sys_out(EntityLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_o(CharactersSpawned, charactersSpawned)
        zox_sys_o(EntityLinks, entityLinks)
        if (renderDistanceDirty->value != zox_dirty_active) {
            continue;
        }
        const byte is_in_spawn_range = renderDistance->value <= terrain_lod_near;
        // remove old characters
        if (!is_in_spawn_range && entityLinks->length) { // charactersSpawned->value &&
            // zox_log("- destroying characters [%i] out of [%i]", entityLinks->length, zox_stats_characters)
            zox_stats_characters -= entityLinks->length;
            for (int j = 0; j < entityLinks->length; j++) {
                zox_delete(entityLinks->value[j])
            }
            clear_memory_component(EntityLinks, entityLinks)
            charactersSpawned->value = 0;
        } else {
            // zox_log("! [%lu] not despawned at [%i]", e, renderDistance->value)
        }
    }
} zox_declare_system(Characters3DespawnSystem)