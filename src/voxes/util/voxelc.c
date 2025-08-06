
// t for terrain
VoxelNode* set_voxelc(
    VoxelNode* node,
    byte target_depth,
    byte3 position,
    byte value,
    byte depth
) {
    byte depth_reached = depth == target_depth;
    if (!depth_reached && is_closed_VoxelNode(node)) {
        open_VoxelNode(node);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            kids[i].value = 0;
        }
    }
    // wait this overrides child nodes, rather than reevaluating them
    if (depth_reached) {
        node->value = value;
    }
    if (depth_reached || !has_children_VoxelNode(node)) {
        return node;
    }
    VoxelNode* kids = get_children_VoxelNode(node);

    const byte dividor = powers_of_two_byte[target_depth - depth - 1];
    //const byte3 node_position = position;
    //byte3_modulus_byte(&node_position, dividor);
    byte3 node_position = (byte3) {
        position.x / dividor,
        position.y / dividor,
        position.z / dividor
    };
    byte3_modulus_byte(&position, dividor);
    byte node_index = byte3_octree_array_index(node_position);

    node = &kids[node_index];
    depth++;

    return set_voxelc(
        node,
        target_depth,
        position,
        value,
        depth);
}