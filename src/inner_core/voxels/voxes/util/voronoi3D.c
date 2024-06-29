// critical for finding voronoi index from a position

#define closest_dist_check_macro(x, y, z) {\
    const float dist = float3_distance(point_f3, float3_add(region_point, (float3) { x, y, z }));\
    if (dist < smallestDistance) {\
        smallestDistance = dist;\
        smallestIndex = i;\
    }\
}

int get_closest_index3(const byte3 point, byte3 *points, int points_length, byte3 size) {
    const float3 point_f3 = byte3_to_float3(point);
    float smallestDistance = 100000; // float.MaxValue;
    float smallestIndex = 0;
    for (int i = 0; i < points_length; i++) {
        const float3 region_point = byte3_to_float3(points[i]);
        for (float x = -1; x <= 1; x++) {
            for (float y = -1; y <= 1; y++) {
                for (float z = -1; z <= 1; z++) {
                    closest_dist_check_macro(x * size.x, y * size.y, z * size.z)
                }
            }
        }
    }
    return smallestIndex;
}

void voronoi3D(ChunkOctree *node, const byte3 size, const unsigned char max_colors, unsigned char black_voxel) {
    const int amplify_points = 16;
    const int points_length = (int) (size.x * 1.6f);
    const int voxels_length = size.x * size.y * size.z;
    const float pointCloseness = size.x / 5;
    byte3 position = byte3_zero;
    byte3 points[points_length];
    unsigned char regions[points_length];
    unsigned char voxels[voxels_length];
    for (int i = 0; i < points_length; i++) points[i] = byte3_zero;
    for (int i = 0; i < points_length; i++) {
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
        regions[i] = 1 + rand() % (max_colors * amplify_points);
    }
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                int region_index = get_closest_index3(position, points, points_length, size);
                int index = byte3_array_index(position, size);
                voxels[index] = regions[region_index];
            }
        }
    }
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
                if (position.x != size.x - 1 || position.y == size.y - 1 || position.z == size.z - 1) {
                    byte3 position_right = byte3_right(position);
                    if (position_right.x == size.x) position_right.x = 0;
                    int index_right = byte3_array_index(position_right, size);
                    voxel_right = voxel != voxels[index_right];
                }
                // up
                if (position.y != size.y - 1 || position.x == size.x - 1 || position.z == size.z - 1) {
                    byte3 position_up = byte3_up(position);
                    if (position_up.y == size.y) position_up.y = 0;
                    int index_up = byte3_array_index(position_up, size);
                    voxel_up = voxel != voxels[index_up];
                }
                // back
                if (position.z != size.z - 1 || position.x == size.x - 1 || position.y == size.y - 1) {
                    byte3 position_forward = byte3_front(position);
                    if (position_forward.z == size.z) position_forward.z = 0;
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
                byte3 node_position = position;
                if (black_voxel && is_darken[index]) {
                    set_octree_voxel(node, &node_position, &set_voxel_black, 0);
                } else {
                    byte2 set_voxel = (byte2) { voxels[index] % max_colors, max_octree_depth };
                    if (set_voxel.x == 0) set_voxel.x = 1;
                    set_octree_voxel(node, &node_position, &set_voxel, 0);
                }
            }
        }
    }
}
