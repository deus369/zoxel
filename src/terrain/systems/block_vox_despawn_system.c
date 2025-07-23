void destroy_block_voxes(ecs_world_t *world, VoxelNode *node) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        if (!destroy_node_entity_VoxelNode(world, node)) {
            zox_log_error("failed to destroy voxel instance.")
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            destroy_block_voxes(world, &kids[i]);
        }
    }
}

void BlockVoxDespawnSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxelNodeDirty)
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(RenderLod)
    zox_sys_out(VoxelNode)
    zox_sys_out(BlocksSpawned)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxelNodeDirty, voxelNodeDirty)
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(BlocksSpawned, blocksSpawned)
        // either voxel node is dirty, or we are spawning for first time based on distance changes
        if (voxelNodeDirty->value != zox_dirty_active && !(blocksSpawned->value && renderDistanceDirty->value == zox_dirty_active)) {
            continue;
        }
        // only destroy if outside range
        if (renderLod->value <= block_vox_render_at_lod) {
            continue;
        }
        destroy_block_voxes(world, voxelNode);
        blocksSpawned->value = 0;
        // zox_geter_value(it->entities[i], ChunkPosition, int3, chunk_position)
        // zox_log("+ despawning block voxes at [%ix%ix%i]", chunk_position.x, chunk_position.y, chunk_position.z)
    }
} zox_declare_system(BlockVoxDespawnSystem)