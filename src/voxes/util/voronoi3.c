// critical for finding voronoi index from a position

#define closest_dist_check_macro(x, y, z) {\
    const float dist = float3_distance(point_f3, float3_add(region_point, (float3) { x, y, z }));\
    if (dist < smallestDistance) {\
        smallestDistance = dist;\
        smallestIndex = i;\
    }\
}

int get_closest_index3(const byte3 point, byte3 *points, int points_length, byte length) {
    const float3 point_f3 = byte3_to_float3(point);
    float smallestDistance = 100000; // float.MaxValue;
    float smallestIndex = 0;
    for (int i = 0; i < points_length; i++) {
        const float3 region_point = byte3_to_float3(points[i]);
        for (float x = -1; x <= 1; x++) {
            for (float y = -1; y <= 1; y++) {
                for (float z = -1; z <= 1; z++) {
                    closest_dist_check_macro(x * length, y * length, z * length)
                }
            }
        }
    }
    return smallestIndex;
}

void voronoi3(
    VoxelNode *node,
    const byte target_depth,
    const byte2 voxel_range,
    byte black_voxel,
    byte vregions
) {
    if (!vregions) {
        return;
    }
    byte length = powers_of_two[target_depth];
    // const byte vregions = 64;
    const int points_length = (int) (length * 1.6f);
    const int voxels_length = length * length * length;
    const float pointCloseness = length / 5;
    byte3 position = byte3_zero;
    byte3 points[points_length];
    byte regions[points_length];
    byte region_voxels[voxels_length];
    for (int i = 0; i < points_length; i++) {
        points[i] = byte3_zero;
    }
    for (int i = 0; i < points_length; i++) {
        byte3 point = (byte3) {
            rand() % length,
            rand() % length,
            rand() % length
        };
        int count = 0;
        while (count <= 128) {
            point = (byte3) {
                rand() % length,
                rand() % length,
                rand() % length
            };
            byte isTooClose = 0;
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
            if (!isTooClose) {
                break;
            }
            count++;
        }
        points[i] = point;
        regions[i] = rand() % vregions;
        /*(uint) ((voxel_range.x + rand() % (voxel_range.y - voxel_range.x)) * amplify_points);*/
    }
    for (position.x = 0; position.x < length; position.x++) {
        for (position.y = 0; position.y < length; position.y++) {
            for (position.z = 0; position.z < length; position.z++) {
                int region_index = get_closest_index3(position, points, points_length, length);
                int index = byte3_array_indexl(position, length);
                region_voxels[index] = regions[region_index];
            }
        }
    }
    byte is_darken[voxels_length];
    for (position.x = 0; position.x < length; position.x++) {
        for (position.y = 0; position.y < length; position.y++) {
            for (position.z = 0; position.z < length; position.z++) {
                const int index = byte3_array_indexl(position, length);
                const byte voxel = region_voxels[index];
                byte is_voxel_up = 0;
                byte is_voxel_right = 0;
                byte is_voxel_front = 0;
                // right
                if (position.x != length - 1 || position.y == length - 1 || position.z == length - 1) {
                    byte3 position_right = byte3_right(position);
                    if (position_right.x == length) {
                        position_right.x = 0;
                    }
                    int index_right = byte3_array_indexl(position_right, length);
                    is_voxel_right = voxel != region_voxels[index_right];
                }
                // up
                if (position.y != length - 1 || position.x == length - 1 || position.z == length - 1) {
                    byte3 position_up = byte3_up(position);
                    if (position_up.y == length) {
                        position_up.y = 0;
                    }
                    int index_up = byte3_array_indexl(position_up, length);
                    is_voxel_up = voxel != region_voxels[index_up];
                }
                // back
                if (position.z != length - 1 || position.x == length - 1 || position.y == length - 1) {
                    byte3 position_forward = byte3_front(position);
                    if (position_forward.z == length) {
                        position_forward.z = 0;
                    }
                    int index_forward = byte3_array_indexl(position_forward, length);
                    is_voxel_front = voxel != region_voxels[index_forward];
                }
                // darken
                is_darken[index] = is_voxel_up || is_voxel_right || is_voxel_front;
            }
        }
    }
    // now darken in another pass
    for (position.x = 0; position.x < length; position.x++) {
        for (position.y = 0; position.y < length; position.y++) {
            for (position.z = 0; position.z < length; position.z++) {
                int index = byte3_array_indexl(position, length);
                if (is_darken[index]) {
                    region_voxels[index] = vregions;
                }
            }
        }
    }
    // const byte2 set_voxel_black = (byte2) { black_voxel, target_depth };
    for (position.x = 0; position.x < length; position.x++) {
        for (position.y = 0; position.y < length; position.y++) {
            for (position.z = 0; position.z < length; position.z++) {
                const int index = byte3_array_indexl(position, length);
                const byte region_voxel = region_voxels[index];
                byte value = black_voxel;
                //  set_voxel = (byte2) { black_voxel, target_depth };
                if (region_voxel != vregions) {
                    value = voxel_range.x + (region_voxel % (voxel_range.y - voxel_range.x));
                }
                /*if (voxels[index])
                if (black_voxel && is_darken[index]) {
                    set_octree_voxel(node, &node_position, &set_voxel_black, 0);
                } else {
                    uint voxel_type = voxels[index] % (voxel_range.y);
                    if (voxel_type < voxel_range.x) voxel_type += voxel_range.x;
                }*/
                //byte3 node_position = position;
                //set_octree_voxel(node, &node_position, &set_voxel, 0);
                set_voxelc(
                    node,
                    target_depth,
                    position,
                    value,
                    0);
            }
        }
    }
}
