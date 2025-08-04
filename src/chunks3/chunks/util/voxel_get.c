// used by physics and raycasting
// i think const was the issue
const byte get_sub_node_voxel(
    const VoxelNode *node,
    byte3 *position,
    const byte depth
) {
    if (!node) {
        return 0;
    }
    if (depth == 0 || !has_children_VoxelNode(node)) {
        return node->value;
    }
    const byte new_depth = depth - 1;
    const byte dividor = powers_of_two_byte[new_depth];
    const byte3 node_position = (byte3) {
        position->x / dividor,
        position->y / dividor,
        position->z / dividor
    };
    byte3_modulus_byte(position, dividor);
    const byte child_index = byte3_octree_array_index(node_position);
    VoxelNode* kids = get_children_VoxelNode(node);
    return get_sub_node_voxel(&kids[child_index], position, new_depth);
}

const byte get_sub_node_voxel_locked(
    const VoxelNode *node,
    byte3 *position,
    const byte depth
) {
    read_lock_VoxelNode(node);
    const byte value = get_sub_node_voxel(node, position, depth);
    read_unlock_VoxelNode(node);
    return value;
}

// returns node, also sets voxel
VoxelNode* get_voxel_node_at_depth(
    byte *value,
    const VoxelNode *node,
    byte3 *position,
    byte depth
) {
    if (!node) {
        return NULL;
    }
    // if child nodes closed or depth final, return current node
    if (depth == 0 || !has_children_VoxelNode(node)) {
        *value = node->value;
        return (VoxelNode*) node;
    }
    depth--;
    const byte dividor = powers_of_two_byte[depth];
    const byte3 node_position = (byte3) {
        position->x / dividor,
        position->y / dividor,
        position->z / dividor
    };
    byte3_modulus_byte(position, dividor);
    const byte child_index = byte3_octree_array_index(node_position);
    VoxelNode* kids = get_children_VoxelNode(node);
    return get_voxel_node_at_depth(value, &kids[child_index], position, depth);
}

VoxelNode* get_voxel_node_at_depth2(
    byte *value,
    const VoxelNode *node,
    byte3 *position,
    byte depth
) {
    // if child nodes closed or depth final, return current node
    if (depth == 0) {
        *value = node->value;
        return (VoxelNode*) node;
    }
    if (!has_children_VoxelNode(node)) {
        *value = 0;
        return (VoxelNode*) node;
    }
    depth--;
    const byte dividor = powers_of_two_byte[depth];
    const byte3 node_position = (byte3) {
        position->x / dividor,
        position->y / dividor,
        position->z / dividor
    };
    byte3_modulus_byte(position, dividor);
    const byte child_index = byte3_octree_array_index(node_position);
    VoxelNode* kids = get_children_VoxelNode(node);
    return get_voxel_node_at_depth2(value, &kids[child_index], position, depth);
}

byte get_adjacent_voxel(
    const VoxelNode** neighbors,
    byte direction,
    const VoxelNode* node,
    int3 position,
    byte depth,
    const byte edge_voxel
) {
    if (!node) {
        return edge_voxel;
    }
    byte chunk_index = 0;
    const VoxelNode *anode = get_adjacent_VoxelNode(
        neighbors,
        node,
        position,
        depth,
        direction,
        &chunk_index);
    if (anode && anode->value) {
        return anode->value;
    } else if (!anode) {
        return edge_voxel; // edge of map
    } else {
        return 0;
    }
}

// single voxel check!
byte is_adjacent_solid(
    byte direction,
    const VoxelNode *root_node,
    const VoxelNode **neighbors,
    int3 position,
    byte depth,
    const byte edge_voxel,
    const byte *voxel_solidity
) {
    byte voxel_adjacent = get_adjacent_voxel(
        neighbors,
        direction,
        root_node,
        position,
        depth,
        edge_voxel);
    if (voxel_adjacent == 0) {
        return 0;
    }
    voxel_adjacent--; // remove air from index
    return voxel_solidity[voxel_adjacent];
}

// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// node_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face

byte is_node_solid(
    const byte* solidity,
    const VoxelNode* node
) {
    if (!node || !node->value) {
        return 0;
    } else if (solidity) {
        return solidity && solidity[node->value - 1];
    } else {
        return 1;   // vox colors
    }
}

// delves down a voxel node, but only one one side
byte get_node_sides_all_solid(
    const byte* solidity,
    const VoxelNode* node,
    byte direction,
    byte travel
) {
    if (!node) {
        // zox_log_error("get_node_sides_all_solid has invalid node.");
        return 0;
    }

    // at end of node tree, return if solid
    if (!has_children_VoxelNode(node) || !travel) {
        return is_node_solid(solidity, node);
    }

    VoxelNode* kids = get_children_VoxelNode(node);
    if (!kids) {
        zox_log_error("get_node_sides_all_solid: null children.");
        return 0;
    }

    travel--;
    for (byte i = 0; i < octree_length; i++) {
        const VoxelNode* child = &kids[i];
        const byte3 np = octree_positions_b[i];

        if ((direction == direction_left   && np.x != 0) ||
            (direction == direction_right  && np.x != 1) ||
            (direction == direction_down   && np.y != 0) ||
            (direction == direction_up     && np.y != 1) ||
            (direction == direction_back   && np.z != 0) ||
            (direction == direction_front  && np.z != 1)
        ) {
            continue;
        }

        // check underneath nodes
        if (!get_node_sides_all_solid(solidity, child, direction, travel)) {
            return 0;
        }
    }
    return 1;   // if all children pass, they are all solid
}

byte is_adjacent_all_solid(
    const byte* solidity,
    byte edge_voxel,
    const VoxelNode **neighbors,
    const byte *ndepths,
    const VoxelNode *node,
    int3 position,
    byte dir,
    byte depth
) {
    const VoxelNode* anode = get_adjacentn_VoxelNode(
        neighbors,
        ndepths,
        node,
        position,
        depth,
        dir);
    byte rdir = reverse_direction(dir);
    // return is_node_solid(solidity, anode);
    return anode ? get_node_sides_all_solid(solidity, anode, rdir, depth) : edge_voxel;
    /*
    byte chunk_index = 0;
    const VoxelNode* anode = get_root_adjacent_VoxelNode(
        neighbors,
        root,
        node,
        octree_position,
        node_index,
        node_position,
        depth,
        direction,
        &chunk_index);*/
}

byte get_voxel(
    VoxelNode *node,
    const byte node_depth,
    const byte3 position,
    const byte3 size
) {
    byte voxel = 0;
    if (byte3_in_bounds(position, size)) {
        byte3 temp_position = position;
        voxel = get_sub_node_voxel(node, &temp_position, node_depth);
    }
    return voxel;
}

VoxelNode* get_node_dig(
    VoxelNode *node,
    byte3 *position,
    const byte depth
) {
    if (node == NULL) {
        return NULL;
    }
    if (!has_children_VoxelNode(node) || depth == 0) {
        return node;
    }
    const byte dividor = powers_of_two_byte[depth - 1];
    const byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    VoxelNode* kids = get_children_VoxelNode(node);
    return get_node_dig(&kids[byte3_octree_array_index(node_position)], position, depth - 1);
}

VoxelNode* get_node(
    VoxelNode *node,
    const byte node_depth,
    const byte3 position
) {
    byte3 temp_position = position;
    return get_node_dig(node, &temp_position, node_depth);
}