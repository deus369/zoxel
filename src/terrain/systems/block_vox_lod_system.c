void set_voxel_node_lods(ecs_world_t *world, const VoxelNode *node, byte lod) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        const ecs_entity_t e = get_entity_VoxelNode(node);
        if (zox_valid(e) && zox_has(e, RenderLod)) {
            zox_set(e, RenderLod, { lod })
            // link to new model here
            // if instance block
            if (zox_has(e, InstanceLink)) {
                zox_geter_value(e, InstanceLink, ecs_entity_t, vox)
                zox_geter(e, InstanceLinks, instanceLinks)
                // zox_log("current vox rendering [%s]", zox_get_name(vox))
                const ecs_entity_t new_vox = instanceLinks->value[lod];
                if (new_vox) {
                    zox_set(e, InstanceLink, { new_vox })
                }
                /*if (vox == vox_grass_0 || vox == vox_grass_1 || vox == vox_grass_2) {
                    if (lod == 0) {
                        zox_set(e, InstanceLink, { vox_grass_0 })
                    } else if (lod == 1) {
                        zox_set(e, InstanceLink, { vox_grass_1 })
                    } else {
                        zox_set(e, InstanceLink, { vox_grass_2 })
                    }
                }*/
            }
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            set_voxel_node_lods(world, &kids[i], lod);
        }
    }
}

void BlockVoxLodSystem(ecs_iter_t *it) {
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
            set_voxel_node_lods(world, voxelNode, vox_lod);
        }
    }
} zox_declare_system(BlockVoxLodSystem)