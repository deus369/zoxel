


void raycast_action(ecs_world_t *world, const RaycastVoxelData *data, const unsigned char voxel, unsigned char hit_type) {
    // int3 ray_hit_normal;
    byte3 place_position;
    ecs_entity_t place_chunk;
    if (hit_type == 2) {
        // zox_log("placing air!\n")
        place_position = data->position;
        place_chunk = data->chunk;
    } else {
        // zox_log("placing solid!\n")
        place_position = data->position_last;
        place_chunk = data->chunk_last;
    }
    // zox_log("   > [%ix%ix%i] [%lu]\n", place_position.x, place_position.y, place_position.z, place_chunk)
    // if (place_chunk == 0) {
    if (!zox_valid(place_chunk)) {
        // zox_log(" > no chunk raycasted\n")
        return;
    }
    const int3 chunk_size = zox_get_value(place_chunk, ChunkSize)
    const byte3 chunk_size_b3 = int3_to_byte3(chunk_size);
    zox_get_muter(place_chunk, ChunkOctree, chunk_octree)
    const SetVoxelTargetData datam = { .depth = max_octree_depth, .voxel = voxel, .effect_nodes = 1 };
    SetVoxelData data2 = { .node = chunk_octree, .position = place_position };
    set_voxel(&datam, data2);
    // this should only trigger if voxel updates is air, or solid (vox blocks should not close same nodes)
    // todo: if voxel type == CanBlockGroup
    // todo: only do this on node updated! and it's parent nodes
    if (data->node->nodes) {
        if (voxel == 0) {
            // cleared minivox
            const ecs_entity_t e3 = ((VoxelEntityLink*)data->node->nodes)->value;
            if (zox_valid(e3)) {
                zox_delete(e3)
                free(data->node->nodes);
                data->node->nodes = NULL;
            }
        }
    } else {
        close_same_nodes(chunk_octree, max_octree_depth, 0);
    }


    zox_set(place_chunk, ChunkDirty, { chunk_dirty_state_edited })
    if (zox_has(place_chunk, ChunkNeighbors) && byte3_on_edge(place_position, chunk_size_b3)) {
        const ChunkNeighbors *chunk_neighbors = zox_get(place_chunk, ChunkNeighbors)
        for (int axis = 0; axis < 6; axis++) {
            if (byte3_on_edge_axis(place_position, chunk_size_b3, axis)) {
                zox_set(chunk_neighbors->value[axis], ChunkDirty, { chunk_dirty_state_edited })
            }
        }
    }
}
