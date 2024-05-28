typedef struct {
    unsigned char depth;
    unsigned char voxel;
} SetVoxelTargetData;

typedef struct {
    ChunkOctree *node;
    byte3 position;
    unsigned char depth;
} SetVoxelData;

void set_voxel(const SetVoxelTargetData *datam, SetVoxelData data) {
    data.node->value = datam->voxel;
    if (data.depth == datam->depth || !data.node->nodes) return;
    const unsigned char dividor = powers_of_two_byte[datam->depth - data.depth - 1]; // difference LoD
    byte3 node_position = (byte3) { data.position.x / dividor, data.position.y / dividor, data.position.z / dividor };
    byte3_modulus_byte(&data.position, dividor);
    data.node = &data.node->nodes[byte3_octree_array_index(node_position)];
    data.depth++;
    set_voxel(datam, data);
}

void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    const SetVoxelTargetData datam = { .depth = set_octree_data->y, .voxel = set_octree_data->x };
    SetVoxelData data = { .node = node, .position = *position, .depth = depth };
    set_voxel(&datam, data);
}

/*void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    node->value = set_octree_data->x;
    if (depth == set_octree_data->y || node->nodes == NULL) return;
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}*/

void set_octree_voxel_final(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    if (depth == set_octree_data->y || !node->nodes) {
        node->value = set_octree_data->x;
        return;
    }
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel_final(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}
