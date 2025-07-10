// this is for spawninng voxel
//      should take in event for future voxels
// note: it only supports placing and removing, not swapping
void place_block(ecs_world_t *world, const ecs_entity_t chunk, VoxelNode *node, const byte3 position_local, int3 position_global, const byte voxel, const float3 position_real) {
    if (!node || !zox_valid(chunk)) {
        return;
    }
    zox_geter_value(chunk, NodeDepth, byte, node_depth)
    zox_get_muter(chunk, VoxelNode, base_node)
    float scale = get_terrain_voxel_scale(node_depth);
    // assume we checked if get_voxel == place_voxel
    // need to delete before node updated
    //if (!voxel) {
    if (is_linked_VoxelNode(node)) {
        destroy_node_entity_VoxelNode(world, node);
    }
    //}
    // set node voxel data
    const int3 chunk_size = zox_get_value(chunk, ChunkSize)
    const byte3 chunk_size_b3 = int3_to_byte3(chunk_size);
    // zox_get_muter(chunk, VoxelNode, base_node)
    const SetVoxelTargetData datam = {
        .depth = node_depth,
        .voxel = voxel,
        .effect_nodes = 1,
    };
    SetVoxelData data2 = {
        .node = base_node,
        .position = position_local,
    };
    node = set_voxel(&datam, data2);
    // set after node was updated
    if (voxel && !is_linked_VoxelNode(node)) {
        // spawn node entity here!
        zox_geter(chunk, VoxLink, voxLink)
        zox_geter(voxLink->value, RealmLink, realmLink)
        zox_geter(realmLink->value, VoxelLinks, voxels)
        const byte block_index = voxel - 1;
        if (block_index >= voxels->length) {
            zox_log_error("voxel [%i] is out of range [%i]", block_index, voxels->length)
            return;
        }
        const ecs_entity_t block = voxels->value[block_index];
        spawned_block_data spawned_data = (spawned_block_data) {
            .block_index = block_index,
            .block = block,
            .position_local = position_local,
            .position_global = position_global,
            .position_real = position_real,
            .chunk = chunk,
            .node = node,
            .scale = scale,
        };
        run_hook_spawned_block(world, &spawned_data);
    }

    // if not linked block
    if (!is_linked_VoxelNode(node)) {
        close_same_nodes(world, base_node);
    }

    // - Refresh Meshes
    zox_set(chunk, ChunkLodDirty, { chunk_lod_state_vox_blocks_pre_spawn })
    zox_set(chunk, ChunkMeshDirty, { chunk_dirty_state_trigger })
    if (zox_has(chunk, ChunkNeighbors) && byte3_on_edge(position_local, chunk_size_b3)) {
        zox_geter(chunk, ChunkNeighbors, chunk_neighbors)
        for (byte axis = 0; axis < chunk_neighbors_length; axis++) {
            if (byte3_on_edge_axis(position_local, chunk_size_b3, axis)) {
                zox_set(chunk_neighbors->value[axis], ChunkMeshDirty, { chunk_dirty_state_trigger })
            }
        }
    }
}

void raycast_action(ecs_world_t *world, const RaycastVoxelData *data, const byte voxel, byte hit_type) {
    byte3 position_local;
    int3 position_global;
    float3 position_real;
    ecs_entity_t chunk;
    VoxelNode* node;
    if (hit_type == 2) {
        // zox_log("placing air!\n")
        position_local = data->position;
        position_global = data->position_global;
        position_real = data->position_real;
        chunk = data->chunk;
        node = data->node;
    } else {
        // zox_log("placing solid!\n")
        position_local = data->position_last;
        position_global = data->position_global_last;
        position_real = data->position_real_last;
        chunk = data->chunk_last;
        node = data->node_last;
    }
    place_block(world, chunk, node, position_local, position_global, voxel, position_real);
}