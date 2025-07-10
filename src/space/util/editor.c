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
    if (!zox_valid(local_terrain)) {
        return;
    }
    debug_block_vox_bounds = !debug_block_vox_bounds;
    if (debug_block_vox_bounds) {
        add_physics_debug(world, prefab_block_vox);
    } else {
        remove_physics_debug(world, prefab_block_vox);
    }
    zox_geter(local_terrain, ChunkLinks, chunkLinks)
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hashmap_pair* pair = chunkLinks->value->data[i];
        uint checks = 0;
        while (pair != NULL && checks < max_safety_checks_hashmap) {
            ecs_entity_t chunk = pair->value;
            if (zox_valid(chunk)) {
                zox_geter_value(chunk, BlocksSpawned, byte, blocks_spawned)
                if (blocks_spawned) {
                    zox_geter(chunk, ChunkOctree, node)
                    zox_geter_value(chunk, NodeDepth, byte, node_depth)
                    toggle_debug_bounds_delve(world, node, node_depth, 0);
                }
            }
            pair = pair->next;
            checks++;
        }
    }
}