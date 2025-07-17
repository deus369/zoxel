void toggle_debug_character_bounds(ecs_world_t *world) {
    if (!zox_valid(local_terrain)) {
        return;
    }
    byte action = cycle_cubeline_debug();
    if (!action) {
        return;
    }
    if (action == 1) {
        zox_set(prefab_character3D, DebugCubeLines, { 1 })
        zox_set(prefab_character3D_npc, DebugCubeLines, { 1 })
    } else if (action == 2) {
        zox_set(prefab_character3D, DebugCubeLines, { 0 })
        zox_set(prefab_character3D_npc, DebugCubeLines, { 0 })
    }
    zox_geter(local_terrain, ChunkLinks, chunkLinks)
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hashmap_pair* pair = chunkLinks->value->data[i];
        uint checks = 0;
        while (pair != NULL && checks < max_safety_checks_hashmap) {
            ecs_entity_t chunk = pair->value;
            zox_geter(chunk, EntityLinks, entityLinks)
            for (int j = 0; j < entityLinks->length; j++) {
                ecs_entity_t e2 = entityLinks->value[j];
                if (action == 1) {
                    // zox_log(" - adding debug collider to [%s]", zox_get_name(e2))
                    zox_set(e2, DebugCubeLines, { 1 })
                } else if (action == 2) {
                    zox_set(e2, DebugCubeLines, { 0 })
                }
            }
            pair = pair->next;
            checks++;
        }
    }
}

void key_down_toggle_debug_character_bounds(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_z) {
        toggle_debug_character_bounds(world);
    }
}