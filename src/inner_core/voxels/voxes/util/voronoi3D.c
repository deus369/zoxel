// critical for finding voronoi index from a position

#define closest_dist_check_macro(x, y, z) {\
    const float dist = float3_distance(point2, float3_add(point_f3, (float3) { x, y, z }));\
    if (dist < smallestDistance) {\
        smallestDistance = dist;\
        smallestIndex = i;\
    }\
}

int get_closest_index3(const byte3 point, byte3 *points, int points_length, byte3 size) {
    float3 point_f3 = byte3_to_float3(point);
    float smallestDistance = 100000; // float.MaxValue;
    float smallestIndex = 0;
    for (int i = 0; i < points_length; i++) {
        float3 point2 = byte3_to_float3(points[i]);
        closest_dist_check_macro(0, 0, 0)
        closest_dist_check_macro(-size.x, 0, 0)
        closest_dist_check_macro(size.x, 0, 0)
        closest_dist_check_macro(0, -size.y, 0)
        closest_dist_check_macro(0, size.y, 0)
        closest_dist_check_macro(0, 0, -size.z)
        closest_dist_check_macro(0, 0, size.z)

        /*closest_dist_check_macro(-size.x, 0, -size.z)
        closest_dist_check_macro(-size.x, 0, size.z)
        closest_dist_check_macro(size.x, 0, -size.z)
        closest_dist_check_macro(size.x, 0, size.z)

        closest_dist_check_macro(-size.x, -size.y, -size.z)
        closest_dist_check_macro(-size.x, -size.y, size.z)
        closest_dist_check_macro(size.x, -size.y, -size.z)
        closest_dist_check_macro(size.x, -size.y, size.z)
        closest_dist_check_macro(-size.x, size.y, -size.z)
        closest_dist_check_macro(-size.x, size.y, size.z)
        closest_dist_check_macro(size.x, size.y, -size.z)
        closest_dist_check_macro(size.x, size.y, size.z)*/
    }
    return smallestIndex;
}

void voronoi3D(ChunkOctree *node, const byte3 size, const unsigned char max_colors, unsigned char black_voxel) {
    const int points_length = (int) (size.x * 2.8f);
    const int voxels_length = size.x * size.y * size.z;
    const float pointCloseness = size.x / 5;
    byte3 position = byte3_zero;
    byte3 points[points_length];
    unsigned char regions[points_length];
    unsigned char voxels[voxels_length];
    for (int i = 0; i < points_length; i++) {
        points[i] = byte3_zero;
        byte3 point = (byte3) { rand() % size.x, rand() % size.y, rand() % size.z };
        int count = 0;
        while (count <= 128) {
            point = (byte3) { rand() % size.x, rand() % size.y, rand() % size.z };
            unsigned char isTooClose = 0;
            for (int j = i - 1; j >= 0; j--) {
                byte3 point2 = points[j];
                if (    point.x + pointCloseness > point2.x - pointCloseness &&
                        point.x - pointCloseness < point2.x + pointCloseness &&
                        point.y + pointCloseness > point2.y - pointCloseness &&
                        point.y - pointCloseness < point2.y + pointCloseness &&
                        point.z + pointCloseness > point2.z - pointCloseness &&
                        point.z - pointCloseness < point2.z + pointCloseness)
                {
                    isTooClose = 1;
                    break;
                }
            }
            if (!isTooClose) break;
            count++;
        }
        points[i] = point;
        regions[i] = 1 + rand() % (max_colors);
    }
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                int regionIndex = get_closest_index3(position, points, points_length, size);
                byte3 node_position = position;
                const byte2 set_voxel = (byte2) { regions[regionIndex], max_octree_depth };
                set_octree_voxel(node, &node_position, &set_voxel, 0);
                int index = byte3_array_index(position, size);
                voxels[index] = set_voxel.x;
            }
        }
    }
    if (black_voxel == 0) return;
    unsigned char is_darken[voxels_length];
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                const int index = byte3_array_index(position, size);
                const unsigned char voxel = voxels[index];
                unsigned char voxel_up = 0;
                unsigned char voxel_right = 0;
                unsigned char voxel_front = 0;
                // right
                if (position.x != size.x - 1) {
                    byte3 position_right = byte3_right(position);
                    int index_right = byte3_array_index(position_right, size);
                    voxel_right = voxel != voxels[index_right];
                }
                // up
                if (position.y != size.y - 1) {
                    byte3 position_up = byte3_up(position);
                    int index_up = byte3_array_index(position_up, size);
                    voxel_up = voxel != voxels[index_up];
                }
                // back
                if (position.z != size.z - 1) {
                    byte3 position_forward = byte3_front(position);
                    int index_forward = byte3_array_index(position_forward, size);
                    voxel_front = voxel != voxels[index_forward];
                }
                // darken
                // is_darken[index] = (voxel_right && voxel_up) || (voxel_right && voxel_front) || (voxel_up && voxel_front);
                is_darken[index] = voxel_up || voxel_right || voxel_front;
            }
        }
    }
    const byte2 set_voxel_black = (byte2) { black_voxel, max_octree_depth };
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                const int index = byte3_array_index(position, size);
                if (is_darken[index]) {
                    byte3 node_position = position;
                    set_octree_voxel(node, &node_position, &set_voxel_black, 0);
                }
            }
        }
    }
}
