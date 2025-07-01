byte debug_block_vox_bounds = 0;

void toggle_debug_bounds_delve(ecs_world_t *world, const ChunkOctree *chunk, const byte max_depth, byte depth) {
    if (!chunk->nodes) {
        return;
    }
    if (depth == max_depth) {
        NodeEntityLink *node_entity_link = (NodeEntityLink*) chunk->nodes;
        if (!node_entity_link) {
            return;
        }
        const ecs_entity_t spawned_block = node_entity_link->value;
        if (zox_valid(spawned_block)) {
            if (debug_block_vox_bounds) add_physics_debug(world, spawned_block);
            else remove_physics_debug(world, spawned_block);
        }
    } else {
        depth++;
        for (int i = 0; i < 8; i++) {
            toggle_debug_bounds_delve(world, &chunk->nodes[i], max_depth, depth);
        }
    }
}

void toggle_debug_block_voxes_bounds(ecs_world_t *world) {
    if (!zox_valid(local_terrain)) return;
    debug_block_vox_bounds = !debug_block_vox_bounds;
    if (debug_block_vox_bounds) add_physics_debug(world, prefab_block_vox);
    else remove_physics_debug(world, prefab_block_vox);
    const ChunkLinks *chunkLinks = zox_get(local_terrain, ChunkLinks)
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hashmap_pair* pair = chunkLinks->value->data[i];
        uint checks = 0;
        while (pair != NULL && checks < max_safety_checks_hashmap) {
            ecs_entity_t chunk = pair->value;
            const byte has_block_spawns = zox_get_value(chunk, BlocksSpawned)
            if (has_block_spawns) {
                const ChunkOctree *chunk_data = zox_get(chunk, ChunkOctree)
                toggle_debug_bounds_delve(world, chunk_data, chunk_data->linked, 0);
            }
            /*const BlockSpawns *blockSpawns = zox_get(chunk, BlockSpawns)
            const byte block_spawns_initialized = blockSpawns->value && blockSpawns->value->data;
            if (block_spawns_initialized) {
                for (int j = 0; j < blockSpawns->value->size; j++) {
                    const byte3_hashmap_pair* pair = blockSpawns->value->data[j];
                    uint checks2 = 0;
                    while (pair != NULL && checks2 < max_safety_checks_hashmap) {
                        const ecs_entity_t e2 = pair->value;
                        if (e2 && zox_valid(e2)) {
                            if (debug_block_vox_bounds) add_physics_debug(world, e2);
                            else remove_physics_debug(world, e2);
                        }
                        pair = pair->next;
                        checks2++;
                    }
                }
            }*/

            pair = pair->next;
            checks++;
        }
    }
}
