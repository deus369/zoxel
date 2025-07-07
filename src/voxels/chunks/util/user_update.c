void voxel_action(ecs_world_t *world, const ecs_entity_t chunk, ChunkOctree *node, const byte3 position, const byte voxel, const float3 position_real) {
    if (!node || !zox_valid(chunk)) {
        return;
    }
    zox_get_muter(chunk, ChunkOctree, base_node)
    if (!voxel) {
        unlink_node_ChunkOctree(world, node);
    } else if (node->linked != linked_state) {
        // spawn node entity here!
        zox_geter(chunk, VoxLink, voxLink)
        zox_geter(voxLink->value, RealmLink, realmLink)
        zox_geter(realmLink->value, VoxelLinks, voxels)
        if (voxel - 1 >= voxels->length) {
            zox_log_error("voxel [%i] is out of range [%i]", voxel, voxels->length)
            return;
        }
        const ecs_entity_t block = voxels->value[voxel - 1];
        if (zox_has(block, BlockPrefabLink)) {
            zox_log("+ Todo: Place Block [Vox]: [%ix%ix%i] - depth [%i] - linked: [%i]", position.x, position.y, position.z, base_node->linked, node->linked)
            // real position
            /*
            zox_geter(block, BlockPrefabLink, block_prefab)
            SpawnBlockVox spawn_data = {
                .prefab = block_prefab,
                .vox = zox_get_value(block, ModelLink),
                .block_index = voxel - 1,
                .position_local = position,
                // .position_global =
                .position_real = position_real,
                .scale = 0.25f,
                // .render_lod =
                // .render_disabled =
            };
            if (zox_has(block_prefab, BlockVox)) {
                e2 = spawn_block_vox(world, &spawn_data);
            } else if (zox_has(block_prefab, RendererInstance)) {
                e2 = spawn_block_vox_instanced(world, &spawn_data);
            }*/
        }
    }
    // set node voxel data
    const int3 chunk_size = zox_get_value(chunk, ChunkSize)
    const byte3 chunk_size_b3 = int3_to_byte3(chunk_size);
    // zox_get_muter(chunk, ChunkOctree, base_node)
    const SetVoxelTargetData datam = {
        .depth = base_node->linked,
        .voxel = voxel,
        .effect_nodes = 1,
    };
    SetVoxelData data2 = {
        .node = base_node,
        .position = position,
    };
    set_voxel(&datam, data2);
    close_same_nodes(world, base_node, base_node->linked, 0);

    // - Refresh Meshes
    zox_set(chunk, ChunkLodDirty, { chunk_lod_state_vox_blocks_pre_spawn })
    zox_set(chunk, ChunkMeshDirty, { chunk_dirty_state_trigger })
    if (zox_has(chunk, ChunkNeighbors) && byte3_on_edge(position, chunk_size_b3)) {
        zox_geter(chunk, ChunkNeighbors, chunk_neighbors)
        for (byte axis = 0; axis < chunk_neighbors_length; axis++) {
            if (byte3_on_edge_axis(position, chunk_size_b3, axis)) {
                zox_set(chunk_neighbors->value[axis], ChunkMeshDirty, { chunk_dirty_state_trigger })
            }
        }
    }
}

void raycast_action(ecs_world_t *world, const RaycastVoxelData *data, const byte voxel, byte hit_type) {
    // int3 ray_hit_normal;
    byte3 position;
    ecs_entity_t chunk;
    if (hit_type == 2) {
        // zox_log("placing air!\n")
        position = data->position;
        chunk = data->chunk;
    } else {
        // zox_log("placing solid!\n")
        position = data->position_last;
        chunk = data->chunk_last;
    }
    voxel_action(world, chunk, data->node, position, voxel, data->position_real);
}