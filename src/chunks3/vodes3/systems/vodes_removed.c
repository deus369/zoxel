void remove_vodes(ecs_world_t *world, VoxelNode *node) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        if (!node->value) { // if air
            if (is_linked_VoxelNode(node)) {
                destroy_node_link_VoxelNode(world, node);
            }
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            remove_vodes(world, &kids[i]);
        }
    }
}

// cleans up vodes attached to air
void VodesRemoveSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxelNodeDirty)
    zox_sys_in(BlocksSpawned)
    zox_sys_out(VoxelNode)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxelNodeDirty, voxelNodeDirty)
        zox_sys_i(BlocksSpawned, blocksSpawned)
        zox_sys_o(VoxelNode, node)
        if (voxelNodeDirty->value == zox_dirty_active && blocksSpawned->value) {
            write_lock_VoxelNode(node);
            remove_vodes(world, node);
            write_unlock_VoxelNode(node);
        }
    }
} zox_declare_system(VodesRemoveSystem)