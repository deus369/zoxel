const int terrain_lod_dividor = 3;

unsigned char get_terrain_lod_from_camera_distance(unsigned char distance_to_camera) {
    #ifdef zoxel_voxel_disable_distance_division
        unsigned char lod = max_octree_depth;
    #else
        unsigned char lod = 255;
        if (distance_to_camera <= init_terrain_lod) {
            lod = max_octree_depth;
        } else if (distance_to_camera <= init_terrain_lod + terrain_lod_dividor) {
            lod = max_octree_depth - 1;
        } else if (distance_to_camera <= init_terrain_lod + terrain_lod_dividor * 2) {
            lod = max_octree_depth - 2;
        } else if (distance_to_camera <= init_terrain_lod + terrain_lod_dividor * 3) {
            lod = max_octree_depth - 3;
        } else if (distance_to_camera <= init_terrain_lod + terrain_lod_dividor * 4) {
            lod = max_octree_depth - 4;
        } else if (distance_to_camera <= init_terrain_lod + terrain_lod_dividor * 5) {
            lod = 0;
        }
    #endif
    return lod;
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
        /*unsigned char depth_addition = distance_to_camera / lod_division_dividor;
        unsigned char lod;
        if (depth_addition < init_terrain_lod) {
            lod = max_octree_depth;
        } else {
            unsigned char difference = depth_addition - init_terrain_lod;
            if (difference > max_octree_depth) {
                lod = 0;
            } else {
                lod = max_octree_depth - difference;
            }
        }*/