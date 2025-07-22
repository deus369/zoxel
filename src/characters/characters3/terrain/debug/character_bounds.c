void toggle_debug_character_bounds(ecs_world_t *world) {
    if (!zox_valid(local_terrain)) {
        return;
    }
    byte mode = zox_get_value(prefab_character3, DebugCubeLines)
    cycle_cubeline_debug(&mode);
    zox_prefab_character_set(DebugCubeLines, { mode })
    // zox_set(prefab_character3_npc, DebugCubeLines, { mode })
    zox_geter(local_terrain, ChunkLinks, chunkLinks)
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hashmap_pair* pair = chunkLinks->value->data[i];
        uint checks = 0;
        while (pair != NULL && checks < max_safety_checks_hashmap) {
            ecs_entity_t chunk = pair->value;
            zox_geter(chunk, EntityLinks, entityLinks)
            for (int j = 0; j < entityLinks->length; j++) {
                ecs_entity_t e2 = entityLinks->value[j];
                zox_set(e2, DebugCubeLines, { mode })
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