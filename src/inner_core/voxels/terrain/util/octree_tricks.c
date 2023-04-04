// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
unsigned char is_adjacent_all_solid(unsigned char direction, const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[],
    int3 octree_position, unsigned char node_index, byte3 node_position, unsigned char depth, const unsigned char max_depth, const unsigned char *neighbors_max_depths) {
    unsigned char chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_index, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL || adjacent_node->value == 0) {
        if (adjacent_node == NULL && chunk_index != 0) {
            #ifdef voxels_hide_terrain_edge
                return 1;
            #else
                return 0;
            #endif
        }
        return 0;
    } else if (adjacent_node->nodes && ((chunk_index == 0 && depth < max_depth) || 
        (chunk_index != 0 && depth < neighbors_max_depths[chunk_index - 1]))) {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        for (unsigned char i = 0; i < octree_length; i++) {
            byte3 local_position = octree_positions_b[i];
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
            int3 new_octree_position = int3_add(octree_position, octree_positions[i]);
            unsigned char is_adjacent_solid = is_adjacent_all_solid(direction, root_node, &adjacent_node->nodes[i], neighbors, new_octree_position, i, local_position, depth, max_depth, neighbors_max_depths);
            if (is_adjacent_solid == 0) {
                return 0;
            }
        }
    }
    return 1;
}

#define zoxel_octree_check(direction_name)\
    if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
        octree_position, node_index, node_position, depth, max_depth, neighbors_max_depths))

unsigned char get_max_depth_from_division(unsigned char chunk_division) {
    #ifdef zoxel_voxel_disable_distance_division
        unsigned char max_depth = max_octree_depth;
    #else
        unsigned char depth_addition = chunk_division / lod_division_dividor;
        unsigned char max_depth;
        if (depth_addition < inner_render_buffer) {
            max_depth = max_octree_depth;
        } else {
            unsigned char difference = depth_addition - inner_render_buffer;
            if (difference > max_octree_depth) {
                max_depth = 0;
            } else {
                max_depth = max_octree_depth - difference;
            }
        }
    #endif
    return max_depth;
}

void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    node->value = set_octree_data->x;
    if (depth == set_octree_data->y || node->nodes == NULL) {
        return;
    }
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at 16, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}

unsigned char get_octree_voxel(const ChunkOctree *node, byte3 *position, unsigned char depth) {
    if (node->nodes == NULL || depth == 0) {
        return node->value;
    }
    unsigned char dividor = powers_of_two_byte[depth - 1]; // target - depth - 1];   // starts at 16, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

        // zoxel_log("Found at depth: %i\n", depth);
// printf(" > going down at [%i]: %ix%ix%i\n", depth, position->x, position->y, position->z);
    // printf("    checking [%i]: %ix%ix%i\n", depth, position.x, position.y, position.z);
        // printf("    - set voxel [%i] at depth [%i] [%ix%ix%i]\n", voxel, depth, position.x, position.y, position.z);
        // printf("node closed at [%i]: %ix%ix%i\n", depth, position.x, position.y, position.z);

    // int node_index = int3_array_index(node_position, octree_node_size3);
    // int3 new_position = (int3) { position.x % dividor, position.y % dividor, position.z % dividor };
    /*if (depth == target) {
        return node->value;
    }*/
    // zoxel_log("dividor %i node pos [%ix%ix%i]\n", dividor, node_position.x, node_position.y, node_position.z);
    /*for (unsigned char i = 0; i < octree_length; i++) {
        int3 local_position = octree_positions[i];
        if (int3_equals(node_position, local_position)) {
            int3 new_position = (int3) { position.x % dividor, position.y % dividor, position.z % dividor };
            return get_octree_voxel(&node->nodes[i], new_position, depth - 1);
        }
    }*/