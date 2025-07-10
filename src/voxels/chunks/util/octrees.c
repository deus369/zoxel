void fill_new_octree(ChunkOctree* node, const byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (byte i = 0; i < octree_length; i++) {
            fill_new_octree(&node->nodes[i], voxel, depth);
        }
    } else node->nodes = NULL;
}

// used by physics and raycasting
// i think const was the issue
const byte get_octree_voxel(const ChunkOctree *node, byte3 *position, const byte depth) {
    if (node == NULL) {
        return 0;
    }
    if (depth == 0) {
        return node->value;
    }
    if (node->nodes == NULL) {
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
    const ChunkOctree *child_node = &node->nodes[child_index];
    return get_octree_voxel(child_node, position, new_depth);
}

// returns node, also sets voxel
ChunkOctree* get_voxel_node_at_depth(byte *value, const ChunkOctree *node, byte3 *position, const byte depth) {
    if (!node) {
        return NULL;
    }
    *value = node->value;
    // if child nodes closed or depth final, return current node
    if (depth == 0) {
        return (ChunkOctree*) node;
    }
    if (!node->nodes) {
        return (ChunkOctree*) node;
    }
    const byte dividor = powers_of_two_byte[depth - 1];
    const byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    const byte child_index = byte3_octree_array_index(node_position);
    const ChunkOctree *child_node = &node->nodes[child_index];
    return get_voxel_node_at_depth(value, child_node, position, depth - 1);
}

//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
void close_solid_nodes(ecs_world_t *world, ChunkOctree *node) {
    if (!has_children_ChunkOctree(node)) {
        return;
    }
    // for all children nodes - only check higher nodes if closed children
    for (byte i = 0; i < octree_length; i++) {
        close_solid_nodes(world, &node->nodes[i]);
    }
    byte all_solid = 1;
    byte all_air = 1;
    for (byte i = 0; i < octree_length; i++) {
        // if child node is open still, don't close
        if (node->nodes[i].nodes) {
            all_solid = 0;
            all_air = 0;
            break;
        }
        // checks if all solid or all air
        if (!node->nodes[i].value) {
            all_solid = 0;
        } else if (node->nodes[i].value) {
            all_air = 0;
        }
        if (!all_solid && !all_air) {
            break;
        }
    }
    if (all_solid || all_air) {
        dispose_ChunkOctree(world, node);
    }
}

// todo: make sure we only close blocks that can be grouped together here (we shouldn't group grass etc)
void close_same_nodes(ecs_world_t *world, ChunkOctree *node) {
    if (!has_children_ChunkOctree(node)) {
        return;
    }
    for (byte i = 0; i < octree_length; i++) {
        close_same_nodes(world, &node->nodes[i]);
    }
    byte all_same = 1;
    byte all_same_voxel = 255;
    for (byte i = 0; i < octree_length; i++) {
        if (node->nodes[i].nodes != NULL) {
            return; // if a child node is open, then don't close this node
        }
        const byte node_value = node->nodes[i].value;
        if (all_same_voxel == 255) {
            all_same_voxel = node_value;
        } else if (all_same_voxel != node_value) {
            all_same = 0;
            break;
        }
    }
    if (all_same) {
        node->value = all_same_voxel;
        dispose_ChunkOctree(world, node);
    }
}

void optimize_solid_nodes(ChunkOctree *node) {
    if (node->nodes != NULL) {
        for (byte i = 0; i < octree_length; i++) optimize_solid_nodes(&node->nodes[i]);
        byte voxel_types = 0;
        // byte2 *voxel_counts = malloc(sizeof(byte2) * octree_length);
        byte2 voxel_counts[octree_length];
        for (byte i = 0; i < octree_length; i++) {
            byte node_value = node->nodes[i].value;
            if (node_value == 0) continue;
            byte has_counted = 0;
            for (byte j = 0; j < voxel_types; j++) {
                has_counted = voxel_counts[j].x == node_value;
                if (has_counted) {
                    voxel_counts[j].y++;
                    break;
                }
            }
            if (!has_counted) {
                voxel_counts[voxel_types].x = node_value;
                voxel_counts[voxel_types].y = 0;
                voxel_types++;
            }
        }
        byte2 biggest_count = byte2_zero;
        for (byte j = 0; j < voxel_types; j++) {
            if (voxel_counts[j].y > biggest_count.y) biggest_count = voxel_counts[j];
        }
        if (biggest_count.x != 0) node->value = biggest_count.x;
        // free(voxel_counts);
    }
}

byte get_adjacent_voxel(byte direction, const ChunkOctree *root_node, const ChunkOctree *neighbors[], int3 position, byte depth, const byte edge_voxel) {
    byte chunk_index = 0;
    const ChunkOctree *adjacent_node = find_root_adjacent_ChunkOctree(root_node, position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node && adjacent_node->value) {
        return adjacent_node->value;
    } else if (!adjacent_node) {
        return edge_voxel; // edge of map
    } else {
        return 0;
    }
}

// single voxel check!
byte is_adjacent_solid(byte direction, const ChunkOctree *root_node, const ChunkOctree *neighbors[], int3 position, byte depth, const byte edge_voxel, const byte *voxel_solidity) {
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
byte is_adjacent_all_solid(byte direction, const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[], int3 octree_position, byte node_index, byte3 node_position, byte depth, const byte max_depth, const byte neighbor_depths[], byte edge_voxel, const byte *voxel_solidity) {
    /*byte is_adjacent_solid(direction, root_node, neighbors[], node_position, depth, edge_voxel, voxel_solidity);*/
    byte chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_index, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL) { // || depth == max_depth) {
        return edge_voxel;
    } else if (adjacent_node->value == 0) {
        return 0;
    } else if (voxel_solidity && !voxel_solidity[adjacent_node->value - 1]) {
        return 0;
    } else if (adjacent_node->nodes != NULL && ((chunk_index == 0 && depth < max_depth) || (chunk_index != 0 && depth < neighbor_depths[chunk_index - 1]))) {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
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
            if (is_adjacent_all_solid(direction, root_node, &adjacent_node->nodes[i], neighbors, int3_add(octree_position, octree_positions[i]), i, local_position, depth, max_depth, neighbor_depths, edge_voxel, voxel_solidity) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void random_fill_octree(ChunkOctree* node, byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (int i = 0; i < octree_length; i++) random_fill_octree(&node->nodes[i], voxel, depth);
    } else {
        if (rand() % 101 >= fill_octree_random_rate) {
            node->value = 0;
        } else if (rand() % 101 >= fill_octree_random_rate2) {
            node->value = 2;
        } else if (rand() % 101 >= fill_octree_random_rate3) {
            node->value = 3;
        }
    }
}

void fill_octree(ChunkOctree* node, const byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (byte i = 0; i < octree_length; i++) {
            fill_octree(&node->nodes[i], voxel, depth);
        }
    }
}
// todo: also close nodes if setting, check if all nodes in the block are same

ChunkOctree* set_voxel(const SetVoxelTargetData *datam, SetVoxelData data) {
    byte depth_reached = data.depth == datam->depth;
    if (datam->effect_nodes && !depth_reached && !data.node->nodes) {
        open_ChunkOctree(data.node);
        for (byte i = 0; i < octree_length; i++) {
            data.node->nodes[i].value = data.node->value;
        }
    }
    // wait this overrides child nodes, rather than reevaluating them
    if (depth_reached || datam->voxel) {
        data.node->value = datam->voxel;
    }
    if (depth_reached || !data.node->nodes) {
        return data.node;
    }
    const byte dividor = powers_of_two_byte[datam->depth - data.depth - 1]; // difference LoD
    byte3 node_position = (byte3) { data.position.x / dividor, data.position.y / dividor, data.position.z / dividor };
    byte3_modulus_byte(&data.position, dividor);
    data.node = &data.node->nodes[byte3_octree_array_index(node_position)];
    data.depth++;
    return set_voxel(datam, data);
}

void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, byte depth) {
    const SetVoxelTargetData datam = { .depth = set_octree_data->y, .voxel = set_octree_data->x };
    SetVoxelData data = { .node = node, .position = *position, .depth = depth };
    set_voxel(&datam, data);
}

void set_octree_voxel_final(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, byte depth) {
    if (depth == set_octree_data->y || !node->nodes) {
        node->value = set_octree_data->x;
        return;
    }
    byte dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel_final(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}


byte get_voxel(ChunkOctree *node, const byte node_depth, const byte3 position, const byte3 size) {
    byte voxel = 0;
    if (byte3_in_bounds(position, size)) {
        byte3 temp_position = position;
        voxel = get_octree_voxel(node, &temp_position, node_depth);
    }
    return voxel;
}

ChunkOctree* get_node_dig(ChunkOctree *node, byte3 *position, const byte depth) {
    if (node == NULL) {
        return NULL;
    }
    if (node->nodes == NULL || depth == 0) {
        return node;
    }
    const byte dividor = powers_of_two_byte[depth - 1];
    const byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_node_dig(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

ChunkOctree* get_node(ChunkOctree *node, const byte node_depth, const byte3 position) {
    byte3 temp_position = position;
    return get_node_dig(node, &temp_position, node_depth);
}