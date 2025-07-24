void Characters3DespawnSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(CharacterSpawnZone)
    zox_sys_out(CharactersSpawned)
    zox_sys_out(EntityLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(CharacterSpawnZone, characterSpawnZone)
        zox_sys_o(CharactersSpawned, charactersSpawned)
        zox_sys_o(EntityLinks, entityLinks)
        if (renderDistanceDirty->value != zox_dirty_active) {
            continue;
        }
        // Sometimes characters are in the chunk still when despawning, make sure to check alot!
        if (!characterSpawnZone->value) {
            // safety
            byte has_player = 0;
            for (int j = 0; j < entityLinks->length; j++) {
                if (zox_has(entityLinks->value[j], PlayerCharacter)) {
                    has_player = 1;
                    break;
                }
            }
            if (has_player) {
                zox_log_error("trying to despawn chunk npcs with a player in it...!")
                continue;
            }
            // zox_log("- destroying characters [%i] out of [%i]", entityLinks->length, zox_stats_characters)
            for (int j = 0; j < entityLinks->length; j++) {
                zox_delete(entityLinks->value[j])
            }
            zox_stats_characters -= entityLinks->length;
            clear_memory_component(EntityLinks, entityLinks)
            charactersSpawned->value = 0;
        }
    }
} zox_declare_system(Characters3DespawnSystem)