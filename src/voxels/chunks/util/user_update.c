void voxel_action(ecs_world_t *world, const ecs_entity_t chunk, ChunkOctree *nodes, const byte3 position, const byte voxel, ChunkOctree *parent_node) {
    // zox_log("   > [%ix%ix%i] [%lu]\n", place_position.x, place_position.y, place_position.z, place_chunk)
    // if (place_chunk == 0) {
    if (!zox_valid(chunk)) {
        // zox_log(" > no chunk raycasted\n")
        return;
    }
    const int3 chunk_size = zox_get_value(chunk, ChunkSize)
    const byte3 chunk_size_b3 = int3_to_byte3(chunk_size);
    zox_get_muter(chunk, ChunkOctree, chunk_octree)
    const SetVoxelTargetData datam = { .depth = max_octree_depth, .voxel = voxel, .effect_nodes = 1 };
    SetVoxelData data2 = { .node = chunk_octree, .position = position };
    // shouldb we just set nodes here?
    // oh but it opens up nodes here too
    set_voxel(&datam, data2);
    // this should only trigger if voxel updates is air, or solid (vox blocks should not close same nodes)
    // todo: if voxel type == CanBlockGroup
    // todo: only do this on node updated! and it's parent nodes
    if (nodes) {
        if (voxel == 0) {
            // cleared minivox / voxel entity
            const ecs_entity_t e3 = ((VoxelEntityLink*) nodes)->value;
            if (zox_valid(e3)) {
                zox_delete(e3)
                free(nodes);
                nodes = NULL;
                // if (parent_node)
                parent_node->nodes = nodes;
                // parent_node->nodes[child_index] = nodes;
            }
        }
    } else {
        close_same_nodes(chunk_octree, max_octree_depth, 0);
    }
    zox_set(chunk, ChunkLodDirty, { chunk_lod_state_vox_blocks_pre_spawn })
    zox_set(chunk, ChunkMeshDirty, { chunk_dirty_state_trigger })
    // should be, BlockVoxesDirty

    // if block meta is minivox or vox entity:
    // todo: just check for spawned entity, spawn either minivox or block entity here
    if (zox_has(chunk, ChunkNeighbors) && byte3_on_edge(position, chunk_size_b3)) {
        const ChunkNeighbors *chunk_neighbors = zox_get(chunk, ChunkNeighbors)
        for (byte axis = 0; axis < 6; axis++) {
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
    voxel_action(world, chunk, data->node->nodes, position, voxel, data->node);
}
