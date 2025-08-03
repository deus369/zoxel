
// used by physics and raycasting
// i think const was the issue

const byte get_sub_node_voxel(const VoxelNode *node, byte3 *position, const byte depth) {
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

const byte get_sub_node_voxel_locked(const VoxelNode *node, byte3 *position, const byte depth) {
    read_lock_VoxelNode(node);
    const byte value = get_sub_node_voxel(node, position, depth);
    read_unlock_VoxelNode(node);
    return value;
}

// returns node, also sets voxel
VoxelNode* get_voxel_node_at_depth(byte *value, const VoxelNode *node, byte3 *position, byte depth) {
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

VoxelNode* get_voxel_node_at_depth2(byte *value, const VoxelNode *node, byte3 *position, byte depth) {
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

byte get_adjacent_voxel(byte direction, const VoxelNode *root_node, const VoxelNode *neighbors[], int3 position, byte depth, const byte edge_voxel) {
    byte chunk_index = 0;
    const VoxelNode *adjacent_node = find_root_adjacent_VoxelNode(root_node, position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node && adjacent_node->value) {
        return adjacent_node->value;
    } else if (!adjacent_node) {
        return edge_voxel; // edge of map
    } else {
        return 0;
    }
}

// single voxel check!
byte is_adjacent_solid(byte direction, const VoxelNode *root_node, const VoxelNode *neighbors[], int3 position, byte depth, const byte edge_voxel, const byte *voxel_solidity) {
    byte voxel_adjacent = get_adjacent_voxel(direction, root_node, neighbors, position, depth, edge_voxel);
    if (voxel_adjacent == 0) {
        return 0;
    }
    voxel_adjacent--; // remove air from index
    return voxel_solidity[voxel_adjacent];
}

// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
byte is_adjacent_all_solid(
    byte direction,
    const VoxelNode *root_node,
    const VoxelNode *parent_node,
    const VoxelNode *neighbors[],
    int3 octree_position,
    byte node_index,
    byte3 node_position,
    byte depth,
    const byte max_depth,
    const byte neighbor_depths[],
    byte edge_voxel,
    const byte *voxel_solidity) {
    /*byte is_adjacent_solid(direction, root_node, neighbors[], node_position, depth, edge_voxel, voxel_solidity);*/
    byte chunk_index = 0;
    const VoxelNode *adjacent_node = find_adjacent_VoxelNode(
        root_node,
        parent_node,
        octree_position,
        node_index,
        node_position,
        depth,
        direction,
        neighbors,
        &chunk_index);
    if (adjacent_node == NULL) { // || depth == max_depth) {
        return edge_voxel;
    } else if (adjacent_node->value == 0) {
        return 0;
    } else if (voxel_solidity && !voxel_solidity[adjacent_node->value - 1]) {
        return 0;
    } else if (is_opened_VoxelNode(adjacent_node) &&
        ((chunk_index == 0 && depth < max_depth) || (chunk_index != 0 && depth < neighbor_depths[chunk_index - 1]))) {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        VoxelNode* kids = get_children_VoxelNode(adjacent_node);
        for (byte i = 0; i < octree_length; i++) {
            const byte3 local_position = octree_positions_b[i];
            if (direction == direction_left) {
                if (local_position.x != 0) {
                    continue;
                }
            } else if (direction == direction_right) {
                if (local_position.x != 1) {
                    continue;
                }
            } else if (direction == direction_down) {
                if (local_position.y != 0) {
                    continue;
                }
            } else if (direction == direction_up) {
                if (local_position.y != 1) {
                    continue;
                }
            } else if (direction == direction_back) {
                if (local_position.z != 0) {
                    continue;
                }
            } else if (direction == direction_front) {
                if (local_position.z != 1) {
                    continue;
                }
            } else {
                continue;
            }
            // check underneath nodes
            if (is_adjacent_all_solid(
                direction,
                root_node,
                &kids[i],
                neighbors,
                int3_add(octree_position, octree_positions[i]),
                i,
                local_position,
                depth,
                max_depth,
                neighbor_depths,
                edge_voxel,
                voxel_solidity) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

byte get_voxel(VoxelNode *node, const byte node_depth, const byte3 position, const byte3 size) {
    byte voxel = 0;
    if (byte3_in_bounds(position, size)) {
        byte3 temp_position = position;
        voxel = get_sub_node_voxel(node, &temp_position, node_depth);
    }
    return voxel;
}

VoxelNode* get_node_dig(VoxelNode *node, byte3 *position, const byte depth) {
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

VoxelNode* get_node(VoxelNode *node, const byte node_depth, const byte3 position) {
    byte3 temp_position = position;
    return get_node_dig(node, &temp_position, node_depth);
}