void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    node->value = set_octree_data->x;
    if (depth == set_octree_data->y || node->nodes == NULL) return;
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}

unsigned char get_octree_voxel(const ChunkOctree *node, byte3 *position, unsigned char depth) {
    if (node->nodes == NULL || depth == 0) return node->value;
    unsigned char dividor = powers_of_two_byte[depth - 1]; // target - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
void close_solid_nodes(ChunkOctree *node) {
    // for all children nodes - only check higher nodes if closed children
    if (node->nodes != NULL) {
        for (unsigned char i = 0; i < octree_length; i++) {
            close_solid_nodes(&node->nodes[i]);
        }
    }
    if (node->nodes != NULL) {
        unsigned char all_solid = 1;
        for (unsigned char i = 0; i < octree_length; i++) {
            if (node->nodes[i].nodes != NULL || node->nodes[i].value == 0) {
                all_solid = 0;
                break;
            }
        }
        if (all_solid) {
            close_ChunkOctree(node);
        } else {
            unsigned char all_air = 1;
            for (unsigned char i = 0; i < octree_length; i++) {
                if (node->nodes[i].nodes != NULL || node->nodes[i].value != 0) {
                    all_air = 0;
                    break;
                }
            }
            if (all_air) {
                close_ChunkOctree(node);
            }
        }
    }
}

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