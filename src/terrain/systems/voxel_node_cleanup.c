// Break down our nodes, if they are the same type
void VoxelNodeCleanupSystem(ecs_iter_t *it) {
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
        cleanup_nodes(world, node);
    }
} zox_declare_system(VoxelNodeCleanupSystem)