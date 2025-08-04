void build_vox_tiles(
    VoxelNode *node,
    const byte node_depth,
    const byte2 color_range,
    const byte black_voxel
) {
    const byte length = powers_of_two_byte[node_depth];
    byte3 size = byte3_single(length);
    byte3 pos;

    // Brick dimensions — play with these
    const byte brick_width  = 6;
    const byte brick_height = 2;
    const byte brick_depth  = 6;
    const byte mortar_gap   = 1; // 1-voxel gap around bricks

    for (pos.x = 0; pos.x < size.x; pos.x++) {
        for (pos.y = 0; pos.y < size.y; pos.y++) {
            for (pos.z = 0; pos.z < size.z; pos.z++) {
                // Compute if current pos is inside a brick, or mortar
                bool in_brick_x = (pos.x % (brick_width + mortar_gap)) < brick_width;
                bool in_brick_y = (pos.y % (brick_height + mortar_gap)) < brick_height;
                bool in_brick_z = (pos.z % (brick_depth + mortar_gap)) < brick_depth;

                if (in_brick_x && in_brick_y && in_brick_z) {
                    const byte value = color_range.x + rand() % (color_range.y - color_range.x);
                    set_voxelc(node, node_depth, pos, value, 0);
                } else {
                    set_voxelc(node, node_depth, pos, black_voxel, 0); // Mortar
                }
            }
        }
    }
}
