void voxel_action(ecs_world_t *world, const ecs_entity_t chunk, ChunkOctree *node, const byte3 position, const byte voxel) {
    if (!node) {
        return;
    }
    // zox_log("   > [%ix%ix%i] [%lu]\n", place_position.x, place_position.y, place_position.z, place_chunk)
    if (!zox_valid(chunk)) {
        // zox_log(" > no chunk raycasted\n")
        return;
    }
    zox_get_muter(chunk, ChunkOctree, base_node)
    if (!voxel) {
        // zox_log("+ Attempting to Remove Block: [%ix%ix%i] - depth [%i] - linked: [%i]\n", position.x, position.y, position.z, base_node->linked, node->linked)
        if (unlink_node_ChunkOctree(world, node)) {
            // zox_log(" - = + SUCCESS\n")
            // return;
        }
    } else if (node->linked != linked_state) {
        // spawn node entity here!
        zox_log("+ Todo: Place Block [Vox]: [%ix%ix%i] - depth [%i] - linked: [%i]\n", position.x, position.y, position.z, base_node->linked, node->linked)
    }
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
    // shouldb we just set nodes here?
    // oh but it opens up nodes here too
    set_voxel(&datam, data2);
    close_same_nodes(world, base_node, base_node->linked, 0);
    // this should only trigger if voxel updates is air, or solid (vox blocks should not close same nodes)
    // todo: if voxel type == CanBlockGroup
    // todo: only do this on node updated! and it's parent nodes
    // refresh chunk meshes
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
    // should be, BlockVoxesDirty
    // if block meta is minivox or vox entity:
    // todo: just check for spawned entity, spawn either minivox or block entity here
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
    voxel_action(world, chunk, data->node, position, voxel);
}
