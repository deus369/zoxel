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

void voronoi3D(ChunkOctree *node, const unsigned char target_depth, const byte3 size, const byte2 voxel_range, unsigned char black_voxel) {
    const unsigned char unique_regions = 64;
    const int points_length = (int) (size.x * 1.6f);
    const int voxels_length = size.x * size.y * size.z;
    const float pointCloseness = size.x / 5;
    byte3 position = byte3_zero;
    byte3 points[points_length];
    unsigned char regions[points_length];
    unsigned char region_voxels[voxels_length];
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
        regions[i] = rand() % unique_regions;
        /*(uint) ((voxel_range.x + rand() % (voxel_range.y - voxel_range.x)) * amplify_points);*/
    }
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                int region_index = get_closest_index3(position, points, points_length, size);
                int index = byte3_array_index(position, size);
                region_voxels[index] = regions[region_index];
            }
        }
    }
    unsigned char is_darken[voxels_length];
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                const int index = byte3_array_index(position, size);
                const unsigned char voxel = region_voxels[index];
                unsigned char is_voxel_up = 0;
                unsigned char is_voxel_right = 0;
                unsigned char is_voxel_front = 0;
                // right
                if (position.x != size.x - 1 || position.y == size.y - 1 || position.z == size.z - 1) {
                    byte3 position_right = byte3_right(position);
                    if (position_right.x == size.x) position_right.x = 0;
                    int index_right = byte3_array_index(position_right, size);
                    is_voxel_right = voxel != region_voxels[index_right];
                }
                // up
                if (position.y != size.y - 1 || position.x == size.x - 1 || position.z == size.z - 1) {
                    byte3 position_up = byte3_up(position);
                    if (position_up.y == size.y) position_up.y = 0;
                    int index_up = byte3_array_index(position_up, size);
                    is_voxel_up = voxel != region_voxels[index_up];
                }
                // back
                if (position.z != size.z - 1 || position.x == size.x - 1 || position.y == size.y - 1) {
                    byte3 position_forward = byte3_front(position);
                    if (position_forward.z == size.z) position_forward.z = 0;
                    int index_forward = byte3_array_index(position_forward, size);
                    is_voxel_front = voxel != region_voxels[index_forward];
                }
                // darken
                is_darken[index] = is_voxel_up || is_voxel_right || is_voxel_front;
            }
        }
    }
    // now darken in another pass
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                int index = byte3_array_index(position, size);
                if (is_darken[index]) region_voxels[index] = unique_regions;
            }
        }
    }
    // const byte2 set_voxel_black = (byte2) { black_voxel, target_depth };
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                const int index = byte3_array_index(position, size);
                const unsigned char region_voxel = region_voxels[index];
                byte2 set_voxel = (byte2) { black_voxel, target_depth };
                if (region_voxel != unique_regions) {
                    set_voxel.x = voxel_range.x + (region_voxel % (voxel_range.y - voxel_range.x));
                }
                /*if (voxels[index])
                if (black_voxel && is_darken[index]) {
                    set_octree_voxel(node, &node_position, &set_voxel_black, 0);
                } else {
                    uint voxel_type = voxels[index] % (voxel_range.y);
                    if (voxel_type < voxel_range.x) voxel_type += voxel_range.x;
                }*/
                byte3 node_position = position;
                set_octree_voxel(node, &node_position, &set_voxel, 0);
            }
        }
    }
}
