byte debug_block_vox_bounds = 0;

void toggle_debug_bounds_delve(ecs_world_t *world, const VoxelNode *node) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        const ecs_entity_t e = get_entity_VoxelNode(node);
        if (zox_valid(e)) {
            if (debug_block_vox_bounds) {
                add_physics_debug(world, e);
            } else {
                remove_physics_debug(world, e);
            }
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            toggle_debug_bounds_delve(world, &kids[i]);
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
                    zox_geter(chunk, VoxelNode, node)
                    toggle_debug_bounds_delve(world, node);
                }
            }
            pair = pair->next;
            checks++;
        }
    }
}