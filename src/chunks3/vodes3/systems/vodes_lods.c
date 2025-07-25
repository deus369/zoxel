void set_vode_lods(ecs_world_t *world, const VoxelNode *node, byte lod) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        const ecs_entity_t e = get_entity_VoxelNode(node);
        if (zox_valid(e) && zox_has(e, RenderLod)) {
            zox_set(e, RenderLod, { lod })
            zox_set(e, RenderLodDirty, { zox_dirty_trigger })
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            set_vode_lods(world, &kids[i], lod);
        }
    }
}

void VodesLodSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(RenderDistance)
    zox_sys_in(VoxelNode)
    zox_sys_in(BlocksSpawned)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(BlocksSpawned, blocksSpawned)
        zox_sys_i(VoxelNode, voxelNode)
        if (renderDistanceDirty->value == zox_dirty_active && blocksSpawned->value) {
            const byte vox_lod = distance_to_lod_vox_block(renderDistance->value);
            set_vode_lods(world, voxelNode, vox_lod);
        }
    }
} zox_declare_system(VodesLodSystem)