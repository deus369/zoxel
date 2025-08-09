// todo: make sure we only close blocks that can be grouped together here (we shouldn't group grass etc)
// doesn't close any block voxes
void reduce_voxel_nodes(
    ecs *world,
    VoxelNode *node
) {
    if (!node || !has_children_VoxelNode(node)) {
        return;
    }

    VoxelNode* kids = get_children_VoxelNode(node);
    for (byte i = 0; i < octree_length; i++) {
        reduce_voxel_nodes(world, &kids[i]);
    }

    byte all_same = 1;
    byte all_same_voxel = 255;

    for (byte i = 0; i < octree_length; i++) {
        VoxelNode* child = &kids[i];

        if (is_opened_VoxelNode(child)) {
            return; // if a child node is open, then don't close this node
        }

        const byte node_value = child->value;
        if (all_same_voxel == 255) {
            all_same_voxel = node_value;
        } else if (all_same_voxel != node_value) {
            all_same = 0;
            break;
        }
    }

    if (all_same) {
        node->value = all_same_voxel;
        close_VoxelNode(world, node);
    }
}

// Break down our nodes, if they are the same type
// When VoxelNodeDirty is zox_dirty_active
// TODO: make a flag for Blocks that can group or not - for this
void VoxelNodeCleanupSystem(iter *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(VoxelNodeDirty)
    zox_sys_in(NodeDepth)
    zox_sys_out(VoxelNode)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxelNodeDirty, voxelNodeDirty)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_o(VoxelNode, node)
        if (voxelNodeDirty->value != zox_dirty_active || !nodeDepth->value) {
            continue;
        }
        write_lock_VoxelNode(node);
        reduce_voxel_nodes(world, node);
        write_unlock_VoxelNode(node);
    }
} zoxd_system(VoxelNodeCleanupSystem)