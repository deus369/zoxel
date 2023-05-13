

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