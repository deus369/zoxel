typedef struct {
    byte depth;
    byte voxel;
    // byte depth_only;
    byte effect_nodes;
} SetVoxelTargetData;

typedef struct {
    ChunkOctree *node;
    byte3 position;
    byte depth;
} SetVoxelData;

// todo: also close nodes if setting, check if all nodes in the block are same

void set_voxel(const SetVoxelTargetData *datam, SetVoxelData data) {
    byte depth_reached = data.depth == datam->depth;
    if (datam->effect_nodes && !depth_reached && !data.node->nodes) {
        open_new_ChunkOctree(data.node);
        for (byte i = 0; i < octree_length; i++) data.node->nodes[i].nodes = NULL;
        for (byte i = 0; i < octree_length; i++) data.node->nodes[i].value = data.node->value;
    }
    if (depth_reached || datam->voxel != 0) data.node->value = datam->voxel;
    if (depth_reached || !data.node->nodes) return;
    const byte dividor = powers_of_two_byte[datam->depth - data.depth - 1]; // difference LoD
    byte3 node_position = (byte3) { data.position.x / dividor, data.position.y / dividor, data.position.z / dividor };
    byte3_modulus_byte(&data.position, dividor);
    data.node = &data.node->nodes[byte3_octree_array_index(node_position)];
    data.depth++;
    set_voxel(datam, data);
}

void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, byte depth) {
    const SetVoxelTargetData datam = { .depth = set_octree_data->y, .voxel = set_octree_data->x };
    SetVoxelData data = { .node = node, .position = *position, .depth = depth };
    set_voxel(&datam, data);
}

/*void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, byte depth) {
    node->value = set_octree_data->x;
    if (depth == set_octree_data->y || node->nodes == NULL) return;
    byte dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}*/

void set_octree_voxel_final(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, byte depth) {
    if (depth == set_octree_data->y || !node->nodes) {
        node->value = set_octree_data->x;
        return;
    }
    byte dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel_final(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}


byte get_voxel(ChunkOctree *node, const byte3 position, const byte3 size) {
    byte voxel = 0;
    if (byte3_in_bounds(position, size)) {
        byte3 temp_position = position;
        voxel = get_octree_voxel(node, &temp_position, max_octree_depth);
    }
    return voxel;
}


ChunkOctree* get_node_dig(ChunkOctree *node, byte3 *position, const byte depth) {
    if (node == NULL) return NULL;
    if (node->nodes == NULL || depth == 0) return node;
    const byte dividor = powers_of_two_byte[depth - 1];
    const byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_node_dig(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

ChunkOctree* get_node(ChunkOctree *node, const byte3 position) {
    byte3 temp_position = position;
    return get_node_dig(node, &temp_position, max_octree_depth);
}
